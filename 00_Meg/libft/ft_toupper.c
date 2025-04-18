/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:39:56 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:39:59 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int ch)
{
	if (ch >= 97 && ch <= 122)
		ch -= 32;
	return (ch);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d", ft_toupper('a'));
	printf("%d", ft_toupper('z'));

	return (0);
}
*/
