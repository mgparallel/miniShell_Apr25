/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_create_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:17:57 by menwu             #+#    #+#             */
/*   Updated: 2025/07/19 17:26:43 by menwu            ###   ########.fr       */
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

int		check_if_exit(char *value)
{
		int i;

		i = 0;
		while (value[i])
		{
			if (value[i] == '$')
			{
				if (value[i + 1] && value[i + 1] == '?')
					return (1);
			}
			i++;
		}
		return (0);
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
	{
		if (check_if_exit(new_token->value))
			new_token->in_quote = 1;
		else
			new_token->in_quote = 0;
	}
	else if (type == DOUBLE_QUOTE)
		new_token->in_quote = 2;
	else
		new_token->in_quote = 0;
	lstadd_back(lst, new_token);
	*start = NULL;
}
