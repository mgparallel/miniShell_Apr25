/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:46:59 by menwu             #+#    #+#             */
/*   Updated: 2025/07/16 20:16:00 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

t_files	*duplicate_fn_lst(t_files *lst)
{
	t_files	*new_head;
	t_files	*new_node;
	t_files	*tail;

	new_head = NULL;
	new_node = NULL;
	tail = NULL;
	while (lst)
	{
		new_node = malloc(sizeof(t_files));
		if (!new_node)
			return (free_lst(&new_head), NULL);
		new_node->value = ft_strdup(lst->value);
		if (!new_node->value)
			return (free(new_node), free_lst(&new_head), NULL);
		new_node->next = NULL;
		if (!new_head)
			new_head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		lst = lst->next;
	}
	return (new_head);
}
// void	free_fn(t_files **fn)
// {
// 	t_files	*temp;

// 	while (*fn)
// 	{
// 		temp = (*fn)->next;
// 		if ((*fn)->value)
// 			free((*fn)->value);
// 		free(*fn);
// 		*fn = temp;
// 	}
// }
