/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:25:51 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:25:55 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int arg)
{
	if (arg >= 48 && arg <= 57)
		return (2048);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int main()
{
    char c;

    printf("Enter a character: ");
    scanf("%c",&c);

    if (isdigit(c) == 0)
         printf("%c is not a digit.",c);
    else
         printf("%c is a digit.",c);
    return 0;
}
*/
