/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:11:14 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/19 20:12:13 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	create_pipes(t_exec_data *data, int num_cmds)
{
	int			i;

	data->pipe_fds = malloc(sizeof(int) * 2 * (num_cmds - 1));
	if (!data->pipe_fds)
		return (perror("malloc"), 1);
	i = -1;
	while (++i < num_cmds - 1)
	{
		if (pipe(data->pipe_fds + i * 2) == -1)
		{
			data->num_cmds = i + 1;
			return (perror("pipe"), close_pipes(data), 1);
		}
	}
	return (0);
}

void	redir_pipes(t_exec_data *data, t_files **env)
{
	if (data->num_pids > 0)
		if (dup2(data->pipe_fds[(data->num_pids - 1) * 2], 0) == -1)
			exit_child("dup2:", data, env);
	if (data->num_pids < data->num_cmds - 1)
		if (dup2(data->pipe_fds[data->num_pids * 2 + 1], 1) == -1)
			exit_child("dup2:", data, env);
	close_pipes(data);
}
