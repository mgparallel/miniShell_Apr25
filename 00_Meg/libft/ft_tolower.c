/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:39:44 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:39:46 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int ch)
{
	if (ch >= 65 && ch <= 90)
		ch += 32;
	return (ch);
}
/*
#include <stdio.h>
int     main(void)
{
        printf("%d", ft_tolower('A'));
        printf("%d", ft_tolower('Z'));

        return (0);
}
*/
