/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:35:20 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 18:07:10 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;
	int		j;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1[++i])
		result[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		result[i] = s2[j];
		i++;
	}
	result[len1 + len2] = '\0';
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	char	x[] = "hello";
	char	y[] = " ";

	//x[0] = '\0';

	printf("\nOutput: %s\n", ft_strjoin(x, y));

	return (0);
}
*/
