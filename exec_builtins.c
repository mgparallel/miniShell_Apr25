/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:47:20 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/20 13:00:57 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_without_output(t_cmd *cmd)
{
	if (!cmd->argv)
		return (1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin_no_output(t_cmd *cmds, t_cmd *cmd, t_files **env, int status)
{
	int	i;
	int	flag;

	flag = 0;
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		if (cmd->argc > 2)
			return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
		return (cmd_cd(cmd->argv[1], env));
	}
	i = 0;
	if (ft_strcmp(cmd->argv[0], "export") == 0)
	{
		if (cmd->argc == 1)
			return (declare_env(*env));
		while (++i < cmd->argc)
			if (cmd_export(cmd->argv[i], env) == 2)
				flag = 1;
	}
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		while (++i < cmd->argc)
			cmd_unset(cmd->argv[i], env);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (cmd_exit(cmds, cmd, env, status));
	return (flag);
}

int	exec_builtin(t_cmd *cmd_list, t_cmd *cmd, t_files **env, int exit_status)
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (cmd_pwd(*env));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (cmd_env(*env));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (cmd_echo(cmd->argv + 1));
	return (exec_builtin_no_output(cmd_list, cmd, env, exit_status));
}
