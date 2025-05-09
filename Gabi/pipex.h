/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:29:33 by gapujol-          #+#    #+#             */
/*   Updated: 2025/03/12 16:55:45 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include "libft_updated/libft.h"

typedef struct s_fds
{
	int	fd[2];
	int	**pipe_fds;
	int	heredoc;
}	t_fds;

void	close_fds(t_fds *fds, int num_cmds, char *error_msg, pid_t *pid);
void	redirect_stdio(int i, t_fds *fds, int num_cmds, pid_t *pid);
void	create_pipes(int num_cmds, t_fds *fds, char **argv);
void	exec_command(char **cmd_args, char **envp);

#endif
