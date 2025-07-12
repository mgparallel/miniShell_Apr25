/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:57:05 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 15:12:04 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_token(t_token **head, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(str);
	if (!new->value)
		return (free(new));
	new->type = WORD;
	new->has_leading_space = 1;
	new->next = NULL;
	lstadd_back(head, new);
}

void	update_wildcard_lst(t_files *files, t_token **head)
{
	while (files->value[0] == '.')
		files = files->next;
	while (files)
	{
		new_token(head, files->value);
		files = files->next;
	}
}

void	add_wildcard_token(t_token **lst, t_token *curr, t_files *files)
{
	t_token	*temp;
	t_token	*prev;
	t_token	*head;

	head = NULL;
	prev = *lst;
	if (!prev->next)
	{
		update_wildcard_lst(files, &head);
		*lst = head;
		return ;
	}
	while (prev && prev->next != curr)
		prev = prev->next;
	temp = prev->next->next;
	free(curr->value);
	free(curr);
	update_wildcard_lst(files, &head);
	prev->next = head;
	lstadd_back(lst, temp);
	free_lst(&files);
}
