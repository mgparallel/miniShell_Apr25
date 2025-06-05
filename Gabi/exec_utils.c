/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:47:20 by gapujol-          #+#    #+#             */
/*   Updated: 2025/06/05 21:55:56 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_exit_status(t_cmd *cmd, int exit_status)
{
	int		i;
	char	status;

	while (cmd->connector == PIPE)
	{
		i = -1;
		while (++i < cmd->argc)
		{
			if (ft_strcmp(cmd->argv[i], "$?") == 0)
			{
				status = ft_itoa(exit_status);
				free(cmd->argv[i]);
				cmd->argv[i] = status;
			}
		}
		cmd = cmd->next;
	}
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
