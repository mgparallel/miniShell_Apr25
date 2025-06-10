/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:47:20 by gapujol-          #+#    #+#             */
/*   Updated: 2025/06/09 22:41:01 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_without_output(t_cmd *cmd)
{
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

int	exec_builtin_without_output(t_cmd *cmd, t_cmd **cmds, t_files **env)
{
	int	i;

	if (check_files(cmd->redir_list))
		return (1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		if (cmd->argc > 2)
			return (ft_putstr_fd("cd: too many arguments", 2), 1);
		return (cmd_cd(cmd->argv[1], env));
	}
	i = 0;
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		while (++i < cmd->argc)
			if (cmd_export(cmd->argv[i], env))
				return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		while (++i < cmd->argc)
			cmd_unset(cmd->argv[i], env);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		cmd_exit(cmd, cmds, env);
	return (0);
}
