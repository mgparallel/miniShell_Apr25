/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:24:41 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:24:44 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*temp;
	size_t	total_size;

	total_size = nitems * size;
	if (total_size == 0)
		total_size = 1;
	temp = malloc(total_size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, total_size);
	return (temp);
}
