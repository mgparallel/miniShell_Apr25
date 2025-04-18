/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:26:47 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:26:52 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new -> next = *lst;
		*lst = new;
	}
}
/*
#include <stdio.h>
int main()
{
    // Create a few integer values to store in the list
    int num1 = 3;
    int num2 = 84;
    int num3 = 126;

    // Create the first node (which will be the last in the list)
    t_list *head = ft_lstnew(&num1);

    // Create two more nodes
    t_list *node2 = ft_lstnew(&num2);
    t_list *node3 = ft_lstnew(&num3);

    // Add node2 to the front of the list
    ft_lstadd_front(&head, node2);
    ft_lstadd_front(&head, node3);
    while(head)
{
	printf("%d",*(int *)head->content);
	head = head -> next;
}
    return 0;
}
*/
