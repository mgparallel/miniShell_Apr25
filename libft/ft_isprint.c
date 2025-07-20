/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:26:06 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:26:10 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int arg)
{
	if (arg >= 32 && arg <= 126)
		return (arg);
	else
		return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	int	c;

	c = 0;
	while (c <=255)
	{
		if (ft_isprint(c) != 0)
			printf("%c", c);
		c++;
	}
	return (0);
}
*/
