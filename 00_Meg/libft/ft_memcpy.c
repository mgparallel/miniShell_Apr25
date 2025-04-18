/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:29:37 by menwu             #+#    #+#             */
/*   Updated: 2024/10/11 16:25:06 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	dest[50] = "This is not a test";
	char	src[] = " ";
	char	*p;

	ft_memcpy(dest, src, 5); 
	p = dest;
	while (*p != '\0')
	{
		printf("%c", *p);
		p++;
	}
	return (0);
}
*/
