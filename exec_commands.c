/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:05:52 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/19 20:11:26 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prep_exec(t_cmd *cmds, t_cmd *cmd, t_files **env, int *exit_status)
{
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
	return (0);
}

int	execute_pipeline(t_cmd *cmds, t_cmd *cmd, t_files **env, int *exit_s)
{
	t_exec_data	data;

	data.num_cmds = count_pipeline_cmds(cmd);
	if (data.num_cmds == 1 && is_builtin_without_output(cmd))
	{
		data.status = check_files(cmd->redir_list);
		if (data.status)
			return (data.status);
		if (cmd->argv)
			*exit_s = exec_builtin_no_output(cmds, cmd, env, *exit_s);
		return (*exit_s);
	}
	if (create_pipes(&data, data.num_cmds))
		return (1);
	data.num_pids = -1;
	while (cmd && (++data.num_pids < data.num_cmds))
	{
		data.pid[data.num_pids] = fork();
		if (data.pid[data.num_pids] == -1)
			return (perror("fork"), close_pipes(&data), wait_pids(&data), 1);
		if (data.pid[data.num_pids] == 0)
			return (redir_pipes(&data, env), prep_exec(cmds, cmd, env, exit_s));
		cmd = cmd->next;
	}
	return (close_pipes(&data), signal(SIGINT, SIG_IGN), wait_pids(&data));
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
