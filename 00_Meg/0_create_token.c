/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_create_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:17:57 by menwu             #+#    #+#             */
/*   Updated: 2025/07/16 20:29:32 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var_in_token(t_token **new_token, t_token_type type, char *str)
{
	(*new_token)->value = str;
	(*new_token)->type = type;
	(*new_token)->lst = NULL;
	(*new_token)->next = NULL;
}

void	create_token(char **start, char *end, t_token_type type, t_token **lst)
{
	t_token	*new_token;
	char	*str;

	str = ft_strcpy(*start, end);
	if (!str)
		return ;
	new_token = malloc(sizeof(t_token));
	new_token->value = NULL;
	if (!new_token)
		return ;
	set_var_in_token(&new_token, type, str);
	if (ch_is_space(*(*start - 1)))
		new_token->has_leading_space = 1;
	else
		new_token->has_leading_space = 0;
	if (type == SINGLE_QUOTE)
		new_token->in_quote = 1;
	else if (type == DOUBLE_QUOTE)
		new_token->in_quote = 2;
	else
		new_token->in_quote = 0;
	lstadd_back(lst, new_token);
	*start = NULL;
}
