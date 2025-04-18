/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:35:50 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:36:01 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	i = 0;
	if (!dest || !src)
		return (0);
	if (size == 0)
		return (len_src);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (len_src);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	x[] = "Wat";
	char	y[] = "jsdj";

	//printf("%zu", strlcpy(x, y, 1));
	printf("%zu\n", ft_strlcpy(x, y, 3));
	printf("The string is:%s", x);
	return (0);
}
*/
