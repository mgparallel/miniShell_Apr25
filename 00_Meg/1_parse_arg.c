/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:06:44 by menwu             #+#    #+#             */
/*   Updated: 2025/07/05 20:24:47 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    join_token(t_token **prev, t_token **cur_token)
{
    char *new_value;
    t_token *next_t;

    next_t = (*cur_token)->next;
    new_value = ft_strjoin((*prev)->value, (*cur_token)->value);
    if (!new_value)
        return (printf("Malloc failed\n"), -1);
	else
	{	
        if ((*cur_token)->type == EXIT_CODE)
            (*prev)->type = EXIT_CODE;
		free((*prev)->value);
		(*prev)->value = new_value;
		(*prev)->next = next_t;
		free((*cur_token)->value);
		free(*cur_token);
            
	}
	return (0);
}

int    parse_type_arg(t_token **lst, t_token **cur_token)
{
    t_token *prev;

    if (*lst == *cur_token)
        return (0);
    prev = *lst;
    while (prev->next != *cur_token)
        prev = prev->next;
    if (!(*cur_token)->has_leading_space &&
					prev->type != PIPE && prev->type != REDIRECT)
        return (join_token(&prev, cur_token));
	else
		return (0);
}