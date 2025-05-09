/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:51:19 by gapujol-          #+#    #+#             */
/*   Updated: 2025/03/12 20:28:52 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_stdio(int i, t_fds *fds, int num_cmds, pid_t *pid)
{
	if (i == 0)
	{
		if (dup2(fds->fd[0], 0) == -1 || dup2(fds->pipe_fds[i][1], 1) == -1)
			close_fds(fds, num_cmds, "pipex: dup2", pid);
	}
	else if (i == num_cmds - 1)
	{
		if (dup2(fds->pipe_fds[i - 1][0], 0) == -1 || dup2(fds->fd[1], 1) == -1)
			close_fds(fds, num_cmds, "pipex: dup2", pid);
	}
	else
		if (dup2(fds->pipe_fds[i - 1][0], 0) == -1
				|| dup2(fds->pipe_fds[i][1], 1) == -1)
			close_fds(fds, num_cmds, "pipex: dup2", pid);
	close_fds(fds, num_cmds, NULL, pid);
}

static int	heredoc(t_fds *fds, char *limiter)
{
	int		pipe_hd[2];
	char	*line;

	if (pipe(pipe_hd) == -1)
		close_fds(fds, 0, "pipex: pipe", NULL);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			close(pipe_hd[0]);
			close(pipe_hd[1]);
			close_fds(fds, 0, "pipex: get_next_line", NULL);
		}
		if (ft_strcmp(line, limiter) == 10)
			break ;
		write(pipe_hd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipe_hd[1]);
	return (pipe_hd[0]);
}

void	create_pipes(int num_cmds, t_fds *fds, char **argv)
{
	int	i;

	if (fds->fd[0] == 0)
		fds->fd[0] = heredoc(fds, argv[2]);
	fds->pipe_fds = malloc(sizeof(int *) * (num_cmds - 1));
	if (!fds->pipe_fds)
		close_fds(fds, num_cmds, "pipex: pipe malloc failed", NULL);
	i = -1;
	while (++i < num_cmds - 1)
	{
		fds->pipe_fds[i] = malloc(2 * sizeof(int));
		if (!fds->pipe_fds[i])
			close_fds(fds, i, "pipex: pipe malloc failed", NULL);
	}
	i = -1;
	while (++i < num_cmds - 1)
		if (pipe(fds->pipe_fds[i]) == -1)
			close_fds(fds, num_cmds, "pipex: pipe", NULL);
}
