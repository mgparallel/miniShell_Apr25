/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:48:47 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/19 20:00:52 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	close_pipes(t_exec_data *data)
{
	while (--data->num_cmds >= 0)
	{
		if (data->pipe_fds[data->num_cmds * 2] > 2)
			close(data->pipe_fds[data->num_cmds * 2]);
		if (data->pipe_fds[data->num_cmds * 2 + 1] > 2)
			close(data->pipe_fds[data->num_cmds * 2 + 1]);
	}
	free(data->pipe_fds);
}

int	wait_pids(t_exec_data *data)
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

void	exit_child(char *msg, t_exec_data *data, t_files **env)
{
	perror(msg);
	close_pipes(data);
	free_lst(env);
	exit (1);
}
