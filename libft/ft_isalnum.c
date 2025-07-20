/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:24:58 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:25:01 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int arg)
{
	if (arg >= 48 && arg <= 57)
		return (1);
	else if (arg >= 65 && arg <= 90)
		return (1);
	else if (arg >= 97 && arg <= 122)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	c;

	printf("Please enter a character: ");
	scanf("%c", &c);

	if (ft_isalnum(c) == 0)
		printf("%s is not a letter or a number", &c);
	else
		printf("%s is a letter or a number", &c);

	return (0);
}
*/
