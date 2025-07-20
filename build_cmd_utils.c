/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:05:31 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/19 20:21:22 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*next;

	if (cmd->argv)
	{
		i = -1;
		while (++i < cmd->argc)
			free(cmd->argv[i]);
		free(cmd->argv);
	}
	if (cmd->expand)
		free(cmd->expand);
	while (cmd->redir_list)
	{
		next = cmd->redir_list->next;
		free(cmd->redir_list->filename);
		free(cmd->redir_list);
		cmd->redir_list = next;
	}
	free(cmd);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		free_cmd(cmd);
		cmd = next;
	}
}

int	is_connector(t_token_type type)
{
	return (type == PIPE || type == AND || type == OR);
}

t_redir_t	token_to_redir_type(const char *op)
{
	if (!ft_strcmp(op, "<"))
		return (REDIR_INPUT);
	if (!ft_strcmp(op, ">"))
		return (REDIR_OUTPUT);
	if (!ft_strcmp(op, ">>"))
		return (REDIR_APPEND);
	if (!ft_strcmp(op, "<<"))
		return (REDIR_HEREDOC);
	return (-1);
}
