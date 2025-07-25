/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_if_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 06:17:44 by menwu             #+#    #+#             */
/*   Updated: 2025/07/16 21:04:58 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_alnum_underscore_braces(int arg)
{
	if (!ft_isalnum(arg))
		return (arg == '_' || arg == '{' || arg == '}');
	else
		return (1);
}

void	if_cmd_util(int *cmd_flag, t_token **cur_token)
{
	if (!*cmd_flag)
	{
		(*cur_token)->type = CMD;
		*cmd_flag = 1;
	}
	else
	{
		if ((*cur_token)->type != EXIT_CODE)
			(*cur_token)->type = ARG;
	}
}

int	after_redir_type(t_token **cur_token)
{
	if ((*cur_token)->type != AND && (*cur_token)->type != OR
		&& (*cur_token)->type != PIPE && (*cur_token)->type != REDIRECT)
	{
		(*cur_token)->type = RE_TARGET;
		return (0);
	}
	else
		return (printf("syntax error near unexpected token\n"), 1);
}

void	update_flag(int *cmd_flag, t_token *cur_token)
{
	if (cur_token->type == PIPE || cur_token->type == AND
		|| cur_token->type == OR)
		*cmd_flag = 0;
}

int	if_cmd(t_token **lst)
{
	t_token	*cur_token;
	t_token	*prev;
	int		cmd_flag;

	cur_token = *lst;
	cmd_flag = 0;
	prev = NULL;
	while (cur_token)
	{
		if (prev && prev->type == REDIRECT)
		{
			if (after_redir_type(&cur_token))
				return (1);
		}
		else
		{
			update_flag(&cmd_flag, cur_token);
			if (cur_token->type != REDIRECT && cur_token->type != AND
				&& cur_token->type != OR && cur_token->type != PIPE)
				if_cmd_util(&cmd_flag, &cur_token);
		}
		prev = cur_token;
		cur_token = cur_token->next;
	}
	return (0);
}
