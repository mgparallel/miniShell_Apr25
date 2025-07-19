/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:10:02 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/19 20:12:01 by gapujol-         ###   ########.fr       */
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
