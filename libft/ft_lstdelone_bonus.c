/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:45:29 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 14:45:33 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
/*
void	del(void *content)
{
	free(content);
}

#include <stdio.h>
void	*print_lst(t_list *lst)
{
	while (lst)
	{
		printf("%s", (char *)(lst->content));
		lst = lst->next;
	}
	printf("NULL\n");
}

int	main(void)
{
    // Create a list
    t_list *list = ft_lstnew(strdup("First"));
    list->next = ft_lstnew(strdup("Second"));
    list->next->next = ft_lstnew(strdup("Third"));

    printf("Original list: ");

    // Delete the second node
    ft_lstdelone(list->next, del);

    // Set the next pointer of the first node to the third node
    t_list *temp = list->next->next;
    list->next = temp;

    printf("List after deleting second node: ");
    

    // Clean up remaining nodes
    while (list)
    {
        t_list *temp = list->next;
        ft_lstdelone(list, del);
        list = temp;
    }

    return 0;
}*/
