/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:05:52 by gapujol-          #+#    #+#             */
/*   Updated: 2025/06/09 22:45:28 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_io(t_redir *list)
{
    int	fd;

    while (list)
    {
        if (list->type == REDIR_INPUT)
            fd = open(list->filename, O_RDONLY);
        else if (list->type == REDIR_OUTPUT)
            fd = open(list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (list->type == REDIR_APPEND)
            fd = open(list->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (list->type == REDIR_HEREDOC)
            fd = heredoc(list->filename);
        if (fd < 0)
            return (1);
        if (list->type == REDIR_INPUT || list->type == REDIR_HEREDOC)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO);
        close(fd);
        list = list->next;
    }
    return (0);
}

int	heredoc(char *delimiter)
{
	int		pipe_hd[2];
	char	*line;

	if (pipe(pipe_hd) == -1)
		return (perror("pipe:"), 1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			return (perror("heredoc:"), close_pipe(pipe_hd), 2);
		if (ft_strcmp(line, delimiter) == 10)
			break ;
		write(pipe_hd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipe_hd[1]);
	return (pipe_hd[0]);
}

void	check_arg(t_cmd *cmd, t_cmd **cmds)
{
	char	code;

	if (is_numeric(cmd->argv[1]))
	{
		code = ft_atoi(cmd->argv[1]);
		free_cmds(cmds);
		exit(code);
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		free_cmds(cmds);
		exit(2);
	}
}

void	clean_exit(t_cmd *cmd, t_cmd **cmds, t_files *env, t_exec_data *data)
{
	close_pipes(data->prev_pipe, data->curr_pipe);
	free_env(&env);
	if (cmd->argc == 1)
	{
		free_cmds(cmds);
		exit (0);
	}
	if (cmd->argc == 2)
		check_arg(cmd, cmds);
	ft_putstr_fd("exit: too many arguments", 2);
}

int	count_pipeline_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd && cmd->connector == PIPE)
	{
		count++;
		cmd = cmd->next;
	}
	return (count + 1); // Incluir el último sin PIPE
}


int	execute_pipeline(t_cmd *start_cmd, t_files **env, char	*exit_status)
{
	t_exec_data	data;
	t_cmd	*cmd;
	int		i;
	int		j;
	int		num_cmds;

	num_cmds = count_pipeline_cmds(start_cmd);
	cmd = start_cmd;
	if (num_cmds == 1 && is_builtin_without_output(cmd))
		return (exec_builtin_without_output(cmd->argv, exit_status));
	data.pipe_fds = malloc(sizeof(int) * 2 * (num_cmds - 1));
	if (!data.pipe_fds)
		return (perror("malloc:"), 1);
	i = -1;
	while (++i < num_cmds - 1)
		if (pipe(data.pipe_fds + i * 2) == -1)
			return (perror("pipe"), free(data.pipe_fds), 1);
	i = -1;
	while (cmd && (++i < num_cmds))
	{
		pid_t pid = fork();
		char	**environ;
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			if (i > 0)
				dup2(data.pipe_fds[(i - 1) * 2], STDIN_FILENO);
			if (i < num_cmds - 1)
				dup2(data.pipe_fds[i * 2 + 1], STDOUT_FILENO);
			j = -1;
			while (++j < 2 * (num_cmds - 1))
				close(data.pipe_fds[j]);
			redirect_io(cmd->redir_list);
			if (is_builtin(cmd->argv))
				exit(exec_builtin(cmd->argv));
			else
			{
				environ = list_to_array(*env);
				execve(cmd->argv[0], cmd->argv, environ);
				free_list(environ);
				perror("execve");
			}
		}
		else
		{
			data.pid[i] = pid;
			data.num_pids++;
		}
		cmd = cmd->next;
	}
	j = -1;
	while (++j < 2 * (num_cmds - 1))
		close(data.pipe_fds[j]);
	// Esperar a todos
	int status;
	j = -1;
	while (++j < data.num_pids)
		waitpid(data.pid[j], &status, 0);
	if (i == data.num_pids - 1)
		if (WIFEXITED(status))
			*exit_status = WEXITSTATUS(status);
	return (0);
}

char *expand_exit_code(const char *str, const char *status_str)
{
    size_t  len;
    int		i;
    int		count;
	char	*new_str;
	
	count = 0;
    len = ft_strlen(status_str);
	i = -1;
    // Contar ocurrencias de $?
    while (str[++i])
        if (str[i] == '$' && str[i + 1] == '?')
            count++;
    // Si no hay $? devolver copia directa
    if (count == 0)
        return (ft_strdup(str));
    new_str = malloc(ft_strlen(str) + count * (len - 2) + 1);
    if (!new_str)
        return (NULL);
    i = 0;
    while (*str)
    {
        if (str[0] == '$' && str[1] == '?')
        {
            ft_strcpy(&new_str[i], status_str);
            i += len;
            str += 2;
        }
        else
            new_str[i++] = *str++;
    }
    new_str[i] = '\0';
    return (new_str);
}

void	expand_pipeline_exit_status(t_cmd *cmd, char exit_status)
{
    char	*status_str;
    t_cmd	*current;
	t_redir *r;
	int		i;

	status_str = ft_itoa(exit_status);
	current = cmd;
    while (current)
    {
        // Expandir en argv
		i = -1;
        while (++i < current->argc)
            current->argv[i] = expand_exit_code(current->argv[i], status_str);

        // Expandir en redirecciones
        r = current->redir_list;
        while (r)
        {
            r->filename = expand_exit_code(r->filename, status_str);
            r = r->next;
        }
		if (current->connector != PIPE)
        	break;
        current = current->next;
    }
    free(status_str);
}

int	exec_commands(t_cmd *cmd_list, t_files *env, char *exit_status)
{
    t_cmd		*cmd;
	
	cmd = cmd_list;
    while (cmd)
    {
        // 1. Expandir $? en argv y redir->filename del pipeline
        expand_pipeline_exit_status(cmd, *exit_status);

        // 2. Ejecutar pipeline
        execute_pipeline(cmd, &env, exit_status);

        // 3. Saltar al próximo grupo de comandos (después del pipeline)
        while (cmd && cmd->connector == PIPE)
            cmd = cmd->next;

        // 4. Evaluar si ejecutar el siguiente grupo según el conector
        if (cmd && ((cmd->connector == AND && exit_status != 0) ||
                    (cmd->connector == OR && exit_status == 0)))
            // Saltar hasta próximo && o || o NULL
            while (cmd && cmd->connector == PIPE)
                cmd = cmd->next;
        else if (cmd)
            cmd = cmd->next;
    }
}
