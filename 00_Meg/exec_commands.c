/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:05:52 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/19 18:18:21 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_heredoc(t_hd_data *d, t_files *env, int exit_status, int in_quote)
{
	if (d->write)
		close(d->pipefd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		write(1, "> ", 2);
		d->line = get_next_line(0);
		if (!d->line)
			ft_putstr_fd("warning: heredoc delimited by end-of-file\n", 2);
		if (!d->line || ft_strcmp(d->line, d->delimiter) == 10)
			break ;
		if (!in_quote)
			expand_var_heredoc(&d->line, exit_status, env);
		if (d->write)
			write(d->pipefd[1], d->line, ft_strlen(d->line));
		free(d->line);
	}
	if (d->line)
		free(d->line);
	if (d->write)
		close(d->pipefd[1]);
	exit(0);
}

int	fork_heredoc(char *delimiter)
{
	t_hd_data	d;

	d.delimiter = delimiter;
	d.write = 0;
	d.pid = fork();
	if (d.pid == -1)
		return (perror("fork"), 1);
	else if (d.pid == 0)
		child_heredoc(&d, NULL, 0, 0);
	signal(SIGINT, SIG_IGN);
	waitpid(d.pid, &d.status, 0);
	if (WIFSIGNALED(d.status))
		if (WTERMSIG(d.status) == SIGINT)
			return (write(1, "\n", 1), 130);
	return (0);
}

int	open_files(t_redir *lst, int fd)
{
	if (lst->type == REDIR_INPUT)
		fd = open(lst->filename, O_RDONLY);
	else if (lst->type == REDIR_OUTPUT)
		fd = open(lst->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (lst->type == REDIR_APPEND)
		fd = open(lst->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	check_files(t_redir *list)
{
	int	fd;

	fd = 0;
	while (list)
	{
		fd = open_files(list, fd);
		if (fd < 0)
			return (perror("open"), 1);
		if (list->type == REDIR_HEREDOC)
		{
			fd = fork_heredoc(list->filename);
			if (fd)
				return (fd);
		}
		if (fd)
			close(fd);
		list = list->next;
	}
	return (0);
}

int	pipe_heredoc(char *delimiter, t_files *env, int exit_status, int in_quote)
{
	t_hd_data	d;

	d.delimiter = delimiter;
	d.write = 1;
	if (pipe(d.pipefd) == -1)
		return (perror("pipe"), -1);
	d.pid = fork();
	if (d.pid == -1)
		return (perror("fork"), close(d.pipefd[0]), close(d.pipefd[1]), -1);
	if (d.pid == 0)
		child_heredoc(&d, env, exit_status, in_quote);
	close(d.pipefd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(d.pid, &d.status, 0);
	if (WIFSIGNALED(d.status))
		if (WTERMSIG(d.status) == SIGINT)
			return (close(d.pipefd[0]), write(2, "\n", 1), -130);
	return (d.pipefd[0]);
}

int	redirect_io(t_redir *lst, t_files *env, int *exit_status)
{
	int	fd;

	fd = 0;
	while (lst)
	{
		fd = open_files(lst, fd);
		if (fd < 0)
			return (perror("open"), 1);
		if (lst->type == REDIR_HEREDOC)
			fd = pipe_heredoc(lst->filename, env, *exit_status, lst->in_quote);
		if (fd < 0)
			return (fd);
		if (lst->type == REDIR_INPUT || lst->type == REDIR_HEREDOC)
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("dup2"), 1);
		if (lst->type == REDIR_OUTPUT || lst->type == REDIR_APPEND)
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (perror("dup2"), 1);
		if (fd > 2)
			close(fd);
		lst = lst->next;
	}
	return (0);
}

int	execute_pipeline(t_cmd *cmds, t_cmd *cmd, t_files **env, int *exit_status)
{
	t_exec_data	data;
	int			num_cmds;
	int			i;

	num_cmds = count_pipeline_cmds(cmd);
	if (num_cmds == 1 && is_builtin_without_output(cmd))
	{
		if (!check_files(cmd->redir_list) && cmd->argv)
			*exit_status = exec_builtin_no_output(cmds, cmd, env, *exit_status);
		return (*exit_status);
	}
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
			if (!cmd->argv)
				exit(0);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (is_builtin(cmd))
				exit(exec_builtin(cmds, cmd, env, *exit_status));
			else
				exec_command(cmd->argv, *env);
		}
		cmd = cmd->next;
	}
	close_pipes(&data, num_cmds - 1);
	signal(SIGINT, SIG_IGN);
	return (wait_for_children(&data));
}

void	exec_commands(t_cmd *cmd_list, t_files **env, int *exit_status)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		expand_pipeline_exit_status(cmd, *exit_status);
		*exit_status = execute_pipeline(cmd_list, cmd, env, exit_status);
		while (cmd && cmd->connector == PIPE)
			cmd = cmd->next;
		while (cmd && ((cmd->connector == AND && *exit_status != 0)
				|| (cmd->connector == OR && *exit_status == 0)))
			cmd = cmd->next;
		if (cmd)
			cmd = cmd->next;
	}
}
