/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:26:23 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 18:49:03 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_size(long n)
{
	int	size;

	size = 0;
	if (n < 0)
		n *= -1;
	if (n == 0)
		size = 1;
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*recursion(long n, char *result, int i)
{
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	if (n == 0)
		result[i - 1] = '0';
	else
	{
		result[i - 1] = n % 10 + '0';
		i--;
		if (n / 10 != 0)
		{
			n = n / 10;
			recursion(n, result, i);
		}
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	long	new;

	new = (long)n;
	size = count_size(new);
	if (new < 0)
		size += 1;
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	recursion(new, result, size);
	result[size] = '\0';
	return (result);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	*str0 = ft_itoa(-9);
	char    *str1 = ft_itoa(8124);
	char    *str2 = ft_itoa(-2147483648LL);
	char    *str3 = ft_itoa(-2147483647);

	printf("\nOur result: %s", str0);
	free(str0);
	printf("\nOur result: %s", str1);
	free (str1);
	printf("\nOur result: %s", str2);
	free(str2);
	printf("\nOur result: %s", str3);
	free(str3);

	return (0);
}
*/
