/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:25:13 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:25:16 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int arg)
{
	if ((arg >= 65 && arg <= 90) || (arg >= 97 && arg <= 122))
		return (1024);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("\nExpected result: %d", isalpha(122));
	printf("\nExpected result: %d", isalpha(32));
	printf("\nExpected result: %d", isalpha(66));
	printf("\nExpected result: %d", isalpha(255));

	printf("\nOur result: %d", ft_isalpha(122));
	printf("\nOur result: %d", ft_isalpha(32));
	printf("\nOur result: %d", ft_isalpha(66));
	printf("\nOur result: %d", ft_isalpha(255));

	return (0);
}
*/
