/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:28:11 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:28:14 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}
/*
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

#include <stdio.h>
int	main(void)
{
	char x = 'a';
	int	y = 1;
	//char z = 'g';

	t_list *head = ft_lstnew(&x);
	t_list *node1 = ft_lstnew(&y);
	//t_list *node2 = ft_lstnew(&z);
	ft_lstadd_front(&head, node1);
	t_list *result = ft_lstlast(head);
	printf("%c", *(char *)(result -> content));
	return (0);
}
*/
