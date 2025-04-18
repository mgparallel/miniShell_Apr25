/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:35:05 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:35:08 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	p;

	if (!s)
		return ;
	p = ft_strlen(s);
	if (!f)
		return ;
	while (p--)
		f(p, &s[p]);
}
/*
static void	capitalize(unsigned int i, char *m)
{
	i = 0;

	while (m[i] != '\0')
	{	
		if (m[i] >= 97 && m[i] <= 122)
			m[i] -= 32;
		i++;
	}
}
	
#include <stdio.h>

int	main(void)
{
	char x[] = "tyfjsbdfbd";
	char y[] = "T";
	char z[] = " ";
	char t[] = "";
	
	ft_striteri(x, &capitalize);
	ft_striteri(y, &capitalize);
	ft_striteri(z, &capitalize);
	ft_striteri(t, &capitalize);
	
	printf("%s\n", x);
	printf("%s\n", y);
	printf("%s\n", z);
	printf("%s\n", t);

	return(0);
}
*/
