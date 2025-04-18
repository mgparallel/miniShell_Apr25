/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:31:02 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:31:06 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (str);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char str[] = "This and that";
	char str2[] = "This and that";

	printf("\nThe expectedis: %s", (char *)memset(str, 'a', 10));
	printf("\nOur result  is: %s", (char *)ft_memset(str2, 'a', 10));

	return (0);
}
*/
