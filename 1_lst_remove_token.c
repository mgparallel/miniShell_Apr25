/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lst_remove_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:05:55 by menwu             #+#    #+#             */
/*   Updated: 2025/07/06 22:48:01 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_rm_token(t_token **lst, t_token **cur_token_ptr)
{
	t_token	*token_to_free;
	t_token	*next_node_in_list;
	t_token	*prev;
	int		if_space;

	if (!lst || !cur_token_ptr || !*cur_token_ptr)
		return (0);
	token_to_free = *cur_token_ptr;
	if_space = token_to_free->has_leading_space;
	next_node_in_list = token_to_free->next;
	if (*lst == token_to_free)
		*lst = next_node_in_list;
	else
	{
		prev = *lst;
		while (prev && prev->next != token_to_free)
			prev = prev->next;
		if (!prev)
			return (if_space);
		prev->next = next_node_in_list;
	}
	free(token_to_free->value);
	free(token_to_free);
	*cur_token_ptr = next_node_in_list;
	return (if_space);
}
