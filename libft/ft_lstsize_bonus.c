/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:28:51 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:28:54 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		len++;
	}
	return (len);
}
/*
#include <stdio.h>
int	main(void)
{
	char	x = 'p';
	int	y = 1;
	char	z = 'k';
	
	t_list *head = ft_lstnew(&x);
	t_list *node1 = ft_lstnew(&y);
	t_list *node2 = ft_lstnew(&z);
	head -> next = node1;
	node1 -> next = node2;
	printf("%d", ft_lstsize(head));
	return (0);
}
*/
