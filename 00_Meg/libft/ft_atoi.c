/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:24:02 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:24:09 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	def_sign(const char **str, int *sign)
{
	while ((**str >= 9 && **str <= 13) || **str == ' ')
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign *= -1;
		else if (**str == '+')
			*sign *= 1;
		(*str)++;
	}
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	def_sign(&str, &sign);
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
/*
#include <stdlib.h>
#include <stdio.h>
int	main(void)
{
	int val;
	int expect;
	char *str;

	str = "     +--2998";
	val = ft_atoi(str); 
	expect = atoi(str);
	printf("Our number = %d", val);
	printf("Expected number = %d", expect);
}
*/
