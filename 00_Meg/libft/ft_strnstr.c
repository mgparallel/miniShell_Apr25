/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:38:57 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:38:59 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	j = 0;
	while (big[i] && i < len)
	{
		while (big[i + j] != '\0' && big[i + j] == little [j]
			&& i + j < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
		j = 0;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	x[] = "lorem ipsum dolor sit amet";
	char    y[] = "dolor";

	//x[0] = '\0';
	//printf("\n%s", strnstr(x, y, 8));
	printf("%s\n", ft_strnstr(x, y, 20));

	return (0);
}
*/
