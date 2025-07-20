/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:29:50 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:29:58 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (d < s)
	{
		i = 0;
		while (i++ < n)
			d[i - 1] = s[i - 1];
	}
	else
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int     main(void)
{
        char    x[] = "UFO does exsit";
        char    y[] = "UFO does exsit";
	//char    x[30] = "";
        //char    y[30] = "";
        //char    m[] = "zyx";
        //char    n[] = "zyx";
        memmove(x+5, x+2, 5);
        printf("\nThe expected:%s", x);
        ft_memmove(y+5, y+2, 5);
        printf("\nOur   result:%s", y);

        return (0);
}

int	main(void)
{
	char	x[] = "UFO does exsit";
	char	y[] = "UFO does exsit";
	char	z[] = "zyx";
	char    z2[] = "zyx";

	memmove(x+5, x+3, 2);
	printf("\nThe expected:%s", x);
	ft_memmove(y+5, y+3, 2);
        printf("\nOur   result:%s", y);
	memmove(x, z, 2);
        printf("\nThe expected:%s", x);
        ft_memmove(y, z2, 2);
        printf("\nOur   result:%s", y);	


	return (0);
}
*/
