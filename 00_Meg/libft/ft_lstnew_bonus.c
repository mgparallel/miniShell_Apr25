/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:28:39 by menwu             #+#    #+#             */
/*   Updated: 2024/10/09 18:03:00 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node -> content = content;
	new_node -> next = NULL;
	return (new_node);
}
/*
#include <stdio.h>
int	main(void)
{
	int	x = 42;
	int	y = 27;
	t_list	*node1;
	t_list	*node2;

	node1 = ft_lstnew(&x);
	node2 = ft_lstnew(&y);
	node1 -> next = node2;
	printf("Node1: %d\n", *(int *)node1 -> content);
	printf("Node2: %d\n", *(int *)node1 -> next -> content);
	free(node1);
	free(node2);
	return (0);
}
*/
