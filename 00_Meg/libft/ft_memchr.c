/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:29:07 by menwu             #+#    #+#             */
/*   Updated: 2024/10/09 16:29:45 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*temp;
	size_t				i;

	temp = (const unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (temp[i] == (unsigned char)c)
			return ((void *)temp + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char x[] = "Dln";
	int y = ' ';
	char	*exp;
	char	*res;

	exp = memchr(x, y, 5);
	printf("\n%p", exp);
	res = ft_memchr(x, y, 5);
        printf("\n%p", res);

	return (0);
}
*/
