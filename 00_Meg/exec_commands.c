/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:05:52 by gapujol-          #+#    #+#             */
/*   Updated: 2025/06/24 20:11:28 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_heredoc(char *delimiter, t_files *env, int exit_status)
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
			ft_putstr_fd("warning: heredoc delimited by end-of-file\n", 2);
		else
			expand_var_heredoc(&line, exit_status, env);
		if (!line || ft_strcmp(line, delimiter) == 10)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
    fd = open(".heredoc", O_RDONLY);
	unlink(".heredoc");
	return (fd);
}

int	fork_heredoc(char *delimiter)
{
	char	*line;
    pid_t	pid;
    int		status;

	pid = fork();
    if (pid == -1)
        return (perror("fork"), 1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		while (1)
		{
			write(1, "> ", 2);
			line = get_next_line(0);
			if (!line)
				ft_putstr_fd("warning: heredoc delimited by end-of-file\n", 2);
			if (!line || ft_strcmp(line, delimiter) == 10)
				break ;
			free(line);
		}
		if (line)
			free(line);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
    {
        status = WTERMSIG(status);
		if (status == SIGINT)
			return (write(1, "\n", 1), 130);
		if (status == SIGQUIT)
			return (131);
    }
    else if (WIFEXITED(status))
        status = WEXITSTATUS(status);
    return (status);
}

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
		if (fd < 0)
            return (perror("open"), 1);
        if (list->type == REDIR_HEREDOC)
		{
            fd = fork_heredoc(list->filename);
			if (fd)
				return (fd);
		}
        close(fd);
        list = list->next;
    }
    return (0);
}

int	redirect_io(t_redir *list, t_files *env, int *exit_status)
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
        if (list->type == REDIR_HEREDOC)
            fd = file_heredoc(list->filename, env, *exit_status);
		if (fd < 0)
            return (perror("open"), 1);
        if (list->type == REDIR_INPUT || list->type == REDIR_HEREDOC)
            if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("dup2"), 1);
        if (list->type == REDIR_OUTPUT || list->type == REDIR_APPEND)
            if (dup2(fd, STDOUT_FILENO) == -1)
				return (perror("dup2"), 1);
        close(fd);
        list = list->next;
    }
    return (0);
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
	return (count + 1);
}

void	close_pipes(t_exec_data *data, int i)
{
	while (--i >= 0)
	{
		close(data->pipe_fds[i * 2]);
		close(data->pipe_fds[i * 2 + 1]);
	}
	free(data->pipe_fds);
}

int	wait_for_children(t_exec_data *data)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	while (++i <= data->num_pids)
		waitpid(data->pid[i], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == SIGINT)
			return (write(1, "\n", 1), 130);
		if (status == SIGQUIT)
			return (printf("quit (core dumped)\n"), 131);
	}
	return (1);
}

void	exit_child(char *msg, t_exec_data *data, int num_cmds, t_files **env)
{
	perror(msg);
	close_pipes(data, num_cmds - 1);
	free_lst(env);
	exit (1);
}

int	execute_pipeline(t_cmd *cmd, t_files **env, int num_cmds, int *exit_status)
{
	t_exec_data	data;
	int		i;
	
	data.pipe_fds = malloc(sizeof(int) * 2 * (num_cmds - 1));
	if (!data.pipe_fds)
		return (perror("malloc"), 1);
	i = -1;
	while (++i < num_cmds - 1)
		if (pipe(data.pipe_fds + i * 2) == -1)
			return (perror("pipe"), close_pipes(&data, i), 1);
	data.num_pids = -1;
	while (cmd && (++data.num_pids < num_cmds))
	{
		data.pid[data.num_pids] = fork();
		if (data.pid[data.num_pids] == -1)
		{
			perror("fork");
			close_pipes(&data, num_cmds - 1);
			wait_for_children(&data);
			return (1);
		}
		if (data.pid[data.num_pids] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (data.num_pids > 0)
				if (dup2(data.pipe_fds[(data.num_pids - 1) * 2], 0) == -1)
					exit_child("dup2:", &data, num_cmds, env);
			if (data.num_pids < num_cmds - 1)
				if (dup2(data.pipe_fds[data.num_pids * 2 + 1], 1) == -1)
					exit_child("dup2:", &data, num_cmds, env);
			close_pipes(&data, num_cmds - 1);
			*exit_status = redirect_io(cmd->redir_list, *env, exit_status);
			if (*exit_status)
			{
				free_lst(env);
				exit(*exit_status);
			}
			if (is_builtin(cmd))
				exit(exec_builtin(cmd, env, 256));
			else
				exec_command(cmd->argv, *env);
		}
		cmd = cmd->next;
	}
	close_pipes(&data, num_cmds - 1);
	signal(SIGINT, SIG_IGN);
	return (wait_for_children(&data));
}

char	*expand_exit_code(const char *str, const char *status_str)
{
    int		count;
    int		i;
    size_t	len_status;
	char	*new_str;
	
	count = 0;
	i = 0;
	len_status = ft_strlen(status_str);
	while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '?')
        {
            count++;
            i += 2;
        }
        else
            i++;
    }
    if (count == 0)
        return (ft_strdup(str));
    new_str = malloc(ft_strlen(str) + count * (len_status - 2) + 1);
    if (!new_str)
        return (NULL);
    i = 0;
    while (*str)
    {
        if (*str == '$' && *(str + 1) == '?')
        {
            ft_memcpy(&new_str[i], status_str, len_status);
            i += len_status;
            str += 2;
        }
        else
            new_str[i++] = *str++;
    }
    new_str[i] = '\0';
    return (new_str);
}


void	expand_pipeline_exit_status(t_cmd *cmd, int exit_status)
{
    char	*status_str;
	char	*tmp;
	t_redir *r;
	int		i;

	status_str = ft_itoa(exit_status);
    while (cmd)
    {
		i = -1;
        while (++i < cmd->argc)
		{
			tmp = cmd->argv[i];
            cmd->argv[i] = expand_exit_code(tmp, status_str);
			free(tmp);
		}
        r = cmd->redir_list;
        while (r)
        {
			if (r->type != REDIR_HEREDOC)
			{
				tmp = r->filename;
            	r->filename = expand_exit_code(tmp, status_str);
				free(tmp);
			}
            r = r->next;
        }
		if (cmd->connector != PIPE)
        	break;
        cmd = cmd->next;
    }
    free(status_str);
}

void	exec_commands(t_cmd *cmd, t_files **env, int *exit_status)
{
	int		num_cmds;

    while (cmd)
    {
        expand_pipeline_exit_status(cmd, *exit_status);
		num_cmds = count_pipeline_cmds(cmd);
		if (num_cmds == 1 && is_builtin_without_output(cmd))
		{
			*exit_status = check_files(cmd->redir_list);
			if (!*exit_status && cmd->argv)
				*exit_status = exec_builtin_without_output(cmd, env, 0);
			if (*exit_status > 255)
				return ;
		}
		else
    		*exit_status = execute_pipeline(cmd, env, num_cmds, exit_status);
        while (cmd && cmd->connector == PIPE)
            cmd = cmd->next;
        if (cmd && ((cmd->connector == AND && *exit_status != 0) ||
                    (cmd->connector == OR && *exit_status == 0)))
            while (cmd && cmd->connector == PIPE)
                cmd = cmd->next;
        else if (cmd)
            cmd = cmd->next;
    }
}
