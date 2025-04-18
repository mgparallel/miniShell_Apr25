/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:39:54 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 14:40:00 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ref;

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
/*
#include <stdio.h>
int	main(void)
{
	char	x = 'k';
	char	y = 'l';
	char	z = 'p';

	t_list *head = ft_lstnew(&x);
	t_list *node1 = ft_lstnew(&y);
	t_list *node2 = ft_lstnew(&z);
	ft_lstadd_back(&head, node1);
	ft_lstadd_back(&head, node2);
	while (head)
	{
		printf("%c", *(char *)head->content);
		head = head->next;
	}
	return (0);
}
*/
