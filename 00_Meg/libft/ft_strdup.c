
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:34:48 by menwu             #+#    #+#             */
/*   Updated: 2024/10/09 18:02:04 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*cpy;
	unsigned int	len;

	len = ft_strlen(s);
	cpy = (char *)malloc((len + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	cpy[len] = '\0';
	while (len-- > 0)
		cpy[len] = s[len];
	return (cpy);
}
/*
#include <stdio.h>
int	main(void)
{
	char x[] = "   ";

	printf("%s", ft_strdup(x));

	return (0);
}
*/
