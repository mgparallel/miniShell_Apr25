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

int	check_files(t_redir *list)
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
		if (list->type == REDIR_HEREDOC)
			unlink(".heredoc");
        if (fd < 0)
            return (perror("open: "), 1);
        close(fd);
        list = list->next;
    }
    return (0);
}

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
		if (list->type == REDIR_HEREDOC)
			unlink(".heredoc");
        if (fd < 0)
            return (perror("open: "), 1);
        if (list->type == REDIR_INPUT || list->type == REDIR_HEREDOC)
            if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("dup2:"), 1);
        if (list->type == REDIR_OUTPUT || list->type == REDIR_APPEND)
            if (dup2(fd, STDOUT_FILENO) == -1)
				return (perror("dup2:"), 1);
        close(fd);
        list = list->next;
    }
    return (0);
}

int	heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			return (close(fd), unlink(".heredoc"), -1);
		if (ft_strcmp(line, delimiter) == 10)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
    fd = open(".heredoc", O_RDONLY);
	return (fd);
}

int	cmd_exit(t_cmd *cmd)
{
	char	code;

	free_lst(&env);
 	rl_clear_history();
	if (cmd->argc == 1)
		return (-1);
	if (cmd->argc == 2)
	{
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


char	execute_pipeline(t_cmd *start_cmd, t_files **env)
{
	t_exec_data	data;
	t_cmd	*cmd;
	int		i;
	int		j;
	int		num_cmds;

	num_cmds = count_pipeline_cmds(start_cmd);
	cmd = start_cmd;
	if (num_cmds == 1 && is_builtin_without_output(cmd))
		return (exec_builtin_without_output(cmd, env));
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
			free(data.pipe_fds);
			if (redirect_io(cmd->redir_list))
				exit_child(env);
			if (is_builtin(cmd->argv))
				exit(exec_builtin(cmd->argv, env));
			else
				exec_command(cmd->argv, *env);
		}
		else
		{
			data.pid[i] = pid;
			data.num_pids++;
		}
		cmd = cmd->next;
	}
	i = -1;
	while (++i < 2 * (num_cmds - 1))
		close(data.pipe_fds[i]);
	// Esperar a todos
	int status;
	i = -1;
	while (++i < data.num_pids)
		waitpid(data.pid[i], &status, 0);
	if (i == data.num_pids - 1)
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
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

void	exec_commands(t_cmd *cmd_list, t_files *env, int *exit_status)
{
    t_cmd		*cmd;
	
	cmd = cmd_list;
    while (cmd)
    {
        // 1. Expandir $? en argv y redir->filename del pipeline
        expand_pipeline_exit_status(cmd, *exit_status);

        // 2. Ejecutar pipeline
        *exit_status = execute_pipeline(cmd, &env);
		if (*exit_status == -1)
			return ;

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
