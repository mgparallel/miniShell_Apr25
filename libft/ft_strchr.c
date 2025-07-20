/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:34:30 by menwu             #+#    #+#             */
/*   Updated: 2024/10/09 18:01:06 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char) ch)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == (char)ch)
		return ((char *)str + i);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	x[] = "ABCDHDSFsdd";
	char	*y;

	printf("Expected result: %p", strchr(x, ' '));
	y = ft_strchr(x, ' ');
	printf("\n%p", y);

	return (0);	
}
*/
