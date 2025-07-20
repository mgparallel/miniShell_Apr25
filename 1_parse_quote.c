/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:07:08 by menwu             #+#    #+#             */
/*   Updated: 2025/07/06 23:03:02 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double_quote(t_token **cur_token)
{
	char	*end_quote;
	char	*dollar_pos;

	end_quote = ft_strrchr((*cur_token)->value, '"');
	if (end_quote[1] != '\0')
	{
		if (update_token(cur_token, (*cur_token)->value, end_quote + 1, WORD)
			== -1)
			return (-1);
	}
	remove_inner_quote(cur_token, '"');
	dollar_pos = ft_strchr((*cur_token)->value, '$');
	if (!dollar_pos)
		return (0);
	(*cur_token)->type = WORD;
	return (1);
}

int	parse_type_quote(t_token **lst, t_token **cur_token)
{
	char	*end_quote;

	if (after_export(lst, cur_token) || var_before_quote(lst, cur_token,
			(*cur_token)->type))
		return (0);
	if ((*cur_token)->type == DOUBLE_QUOTE)
	{
		return (is_double_quote(cur_token));
	}
	else if ((*cur_token)->type == SINGLE_QUOTE)
	{
		end_quote = ft_strrchr((*cur_token)->value, '\'');
		if (end_quote[1] != '\0')
		{
			if (update_token(cur_token, (*cur_token)->value, end_quote + 1,
					WORD) == -1)
				return (-1);
		}
	}
	remove_inner_quote(cur_token, '\'');
	return (0);
}
