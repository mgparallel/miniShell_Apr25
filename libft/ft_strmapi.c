/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:38:26 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 19:10:01 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*result;

	i = 0;
	len = ft_strlen((char *)s);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result || !f)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
static char	capitalize(unsigned int i, char m)
{
	i = 0;

	if (m >= 97 && m <= 122)
		m = m - 32;
	return (m);
}

#include <stdio.h>

int	main(void)
{
	char const x[] = "theh IJ";
	//unsigned int i;
	char *result;

	result = ft_strmapi(x, &capitalize);
	printf("%s\n", result);
	printf("%p\n", result);
	free(result);
	return(0);
}
*/
