/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:27:12 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:27:34 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ref;
	t_list	*temp;

	ref = *lst;
	while (ref)
	{
		temp = ref->next;
		ft_lstdelone(ref, del);
		ref = temp;
	}
	*lst = NULL;
}
