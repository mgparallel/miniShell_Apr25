/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:24:23 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:24:27 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = s;
	while (n > 0)
	{
		*temp = '\0';
		temp++;
		n--;
	}
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	c[] = "Wasistdas";
	size_t	i;
	char *p;

	p = c;
	i = sizeof(c);
	ft_bzero(c, i);
	while (i > 0)
	{
		if (*p == '\0')
			printf("\\0");
		else
			printf("%c", *p);
		p++;
		i--;
	}
	return (0);
}
*/
