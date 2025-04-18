/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:21:13 by menwu             #+#    #+#             */
/*   Updated: 2024/10/06 22:50:50 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*ref;
	t_list	*new_node;
	void	*new_content;

	ref = lst;
	result = NULL;
	while (ref)
	{
		new_content = f(ref->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, new_node);
		ref = ref->next;
	}
	return (result);
}
/*
void	del(void *content)
{
	free (content);
}

void	*f(void *content) //capitalize
{
	char	*m = (char *)content;
	if (*m >= 97 && *m <= 122)
		*m -= 32;
	return (content);
}

#include <stdio.h>
int	main(void)
{
	char	*x = ft_strdup("s");
	char	*y = ft_strdup("i");
	char	*z = ft_strdup("p");

	t_list *head = ft_lstnew(&x);
	t_list *node1 = ft_lstnew(&y);
	t_list *node2 = ft_lstnew(&z);
	ft_lstadd_back(&head, node1);
	ft_lstadd_back(&head, node2);

	t_list *result = ft_lstmap(head, f, del);
	while (result)
	{
		printf("%c\n", *(char *)result->content);
		result = result->next;
	}
	ft_lstclear(&result, del);
	ft_lstclear(&head, del);
	return (0);
}*/
