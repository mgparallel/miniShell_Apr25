/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_tokenizer_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:17:39 by menwu             #+#    #+#             */
/*   Updated: 2025/07/06 22:40:48 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ch_is_space(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n');
}

bool	ch_is_special(char ch)
{
	return (ch == '>' || ch == '<' || ch == '|' || ch == '&');
}

bool	space_special(char ch)
{
	return (ch_is_space(ch) || ch_is_special(ch));
}

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*ref;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ref = *lst;
	while (ref && ref->next)
		ref = ref->next;
	ref->next = new;
}

char	*ft_strcpy(char *start, char *end)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = end - start;
	if (len < 0)
		return (NULL);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = *start;
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
