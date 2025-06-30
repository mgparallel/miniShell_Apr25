/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:06:44 by menwu             #+#    #+#             */
/*   Updated: 2025/07/01 00:06:45 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    join_token(t_token **prev, t_token **cur_token)
{
    char *new_value;
    t_token *next_t;

    next_t = (*cur_token)->next;
    new_value = ft_strjoin((*prev)->value, (*cur_token)->value);
    if (!new_value)
        return ;
    (*prev)->value = new_value;
    (*prev)->next = next_t;
    free(*cur_token);
}

void    parse_type_arg(t_token **lst, t_token **cur_token)
{
    t_token *prev;
    char *var;

    if (*lst == *cur_token)
        return ;
    var = (*cur_token)->value;
    prev = *lst;
    while (prev->next != *cur_token)
        prev = prev->next;
    if_braces(&var);
    if (!(*cur_token)->has_leading_space 
                    && prev->type != PIPE && prev->type != REDIRECT)
        join_token(&prev, cur_token);
}