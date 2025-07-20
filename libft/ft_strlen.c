/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:36:10 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:36:12 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	a[20] = "Today is the day.";
	char	b[20] = " ";
	char	c[30] = "O comes before than 1";

	printf("The correct:\n%zu\n", strlen(a));
	printf("The correct:\n%zu\n", strlen(b));
	printf("The correct:\n%zu\n", strlen(c));
	printf("Our: \n%zu\n", ft_strlen(a));
	printf("Our: \n%zu\n", ft_strlen(b));
	printf("Our: \n%zu\n", ft_strlen(c));

	return (0);
}
*/
