/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:20:49 by gapujol-          #+#    #+#             */
/*   Updated: 2025/03/12 16:53:14 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	wait_for_process(pid_t *pid, int num_process)
{
	int	status;
	int	i;
	int	signal_number;

	i = -1;
	while (++i < num_process)
	{
		waitpid(pid[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			signal_number = WTERMSIG(status);
			ft_putstr_fd("Child process terminated by signal ", 2);
			ft_putnbr_fd(signal_number, 2);
			ft_putchar_fd('\n', 2);
			if (i == num_process - 1)
				exit(128 + signal_number);
		}
		if (i == num_process - 1
			&& WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit(WEXITSTATUS(status));
	}
	free(pid);
}

void	close_fds(t_fds *fds, int num_cmds, char *error_msg, pid_t *pid)
{
	int	i;

	if (fds->fd[0] >= 0)
		close(fds->fd[0]);
	if (fds->fd[1] >= 0)
		close(fds->fd[1]);
	if (fds->pipe_fds)
	{
		i = -1;
		while (++i < num_cmds - 1)
		{
			if (fds->pipe_fds[i][0] >= 0)
				close(fds->pipe_fds[i][0]);
			if (fds->pipe_fds[i][1] >= 0)
				close(fds->pipe_fds[i][1]);
		}
		i = -1;
		while (++i < num_cmds - 1)
			free(fds->pipe_fds[i]);
		free(fds->pipe_fds);
	}
	if (pid)
		free(pid);
	if (error_msg)
		return (perror(error_msg), exit(1));
}

static void	pipex(t_fds *fds, int num_cmds, char **argv, char **envp)
{
	int		i;
	pid_t	*pid;

	create_pipes(num_cmds, fds, argv);
	pid = malloc(sizeof(pid_t) * num_cmds);
	if (!pid)
		close_fds(fds, num_cmds, "pipex: pid malloc failed", NULL);
	i = -1;
	while (++i < num_cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("pipex: fork");
			break ;
		}
		if (pid[i] == 0)
		{
			redirect_stdio(i, fds, num_cmds, pid);
			exec_command(ft_split(argv[i + 2 + fds->heredoc], ' '), envp);
		}
	}
	close_fds(fds, num_cmds, NULL, NULL);
	wait_for_process(pid, i);
}

static void	open_files(int *argc, char **argv, t_fds *fds)
{
	if (*argc > 5 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		fds->fd[0] = 0;
		fds->fd[1] = open(argv[*argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds->fd[1] < 0)
			perror("pipex: outfile");
		(*argc)--;
		fds->heredoc++;
	}
	else
	{
		fds->fd[0] = open(argv[1], O_RDONLY);
		if (fds->fd[0] < 0)
			perror("pipex: infile");
		fds->fd[1] = open(argv[*argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds->fd[1] < 0)
			perror("pipex: outfile");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_fds	fds;

	fds.heredoc = 0;
	if (argc < 5)
	{
		ft_printf("Use: ./pipex file1 cmd1 [...] cmdN file2\n");
		ft_printf("Heredoc: ./pipex here_doc LIMITER cmd1 [...] cmdN file2\n");
		return (1);
	}
	open_files(&argc, argv, &fds);
	pipex(&fds, argc - 3, argv, envp);
	return (0);
}
