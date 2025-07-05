/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:07:08 by menwu             #+#    #+#             */
/*   Updated: 2025/07/05 07:47:29 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// funtion to remove quotes wihin the token->value
void remove_inner_quote(t_token **cur_token, char quote) //a'a'  aa
{
    char *original;
    char *new_value;
	int len;
	int i;

    original = (*cur_token)->value;
	len = ft_strlen(original);
	new_value = malloc(len - 1);
	if (!new_value)
		return ;
	len = 0;
	i = 0;
	while (original[len])
	{
		if (original[len] != quote)
		{	
			new_value[i] = original[len];
			i++;
		}
		len++;
	}
	new_value[i] = '\0';
	free(original);
	(*cur_token)->value = new_value;
	(*cur_token)->type = ARG;
}

// funtion to check if single quote/double quote contains $
// remove outer quotes and deceide if expand
int parse_type_quote(t_token **cur_token)
{
    char *dollar_pos;
    char *end_quote;
	
    if ((*cur_token)->type == DOUBLE_QUOTE)
    {
        end_quote = ft_strrchr((*cur_token)->value, '"');
        if (end_quote[1] != '\0')
        {
			if (update_token(cur_token, (*cur_token)->value, end_quote + 1, WORD) == -1)
				return (-1);
		}
        remove_inner_quote(cur_token, '"');
        dollar_pos = ft_strchr((*cur_token)->value, '$');
		if (!dollar_pos)
			return (0);
        (*cur_token)->type = WORD;
		return (1);
    }
    else if ((*cur_token)->type == SINGLE_QUOTE)
    {
        end_quote = ft_strrchr((*cur_token)->value, '\'');
        if (end_quote[1] != '\0')
        {
			if (update_token(cur_token, (*cur_token)->value, end_quote + 1, WORD) == -1)
				return (-1);
		}
    }
    remove_inner_quote(cur_token, '\'');
    return (0);
}