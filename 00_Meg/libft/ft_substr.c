/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:39:29 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:39:31 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*result;
	size_t		total_len;

	if (!s)
		return (NULL);
	total_len = ft_strlen((char *)s);
	if (start > total_len - 1)
		len = 0;
	else if (start + len > total_len)
		len = total_len - start;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len-- > 0)
	{
		result[len] = s[start + len];
	}
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	char x[] = "The song is mine.";
	char y = 4;
	//char *re; //= ft_substr(x, y, 4);
	
	*re = ft_substr(x, y, 4);
	printf("%s", ft_substr(x, y, 4));

	return (0);
}
*/
