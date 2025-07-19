/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:58:07 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/19 16:31:04 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cmd_args(t_cmd **cmd, int i, char *status_str)
{
	char	*tmp;

	if ((*cmd)->expand[i] == 0)
		return ;
	tmp = (*cmd)->argv[i];
	(*cmd)->argv[i] = expand_exit_code(tmp, status_str);
	free(tmp);
}

void	if_no_redir_hd(t_redir **r, char *status_str)
{
	char	*tmp;

	if ((*r)->in_quote == 1)
		return ;
	tmp = (*r)->filename;
	(*r)->filename = expand_exit_code(tmp, status_str);
	free(tmp);
}

void	expand_pipeline_exit_status(t_cmd *cmd, int exit_status)
{
	char	*status_str;
	t_redir	*r;
	int		i;

	status_str = ft_itoa(exit_status);
	while (cmd)
	{
		i = -1;
		while (++i < cmd->argc)
			update_cmd_args(&cmd, i, status_str);
		r = cmd->redir_list;
		while (r)
		{
			if (r->type != REDIR_HEREDOC)
				if_no_redir_hd(&r, status_str);
			r = r->next;
		}
		if (cmd->connector != PIPE)
			break ;
		cmd = cmd->next;
	}
	free(status_str);
}
