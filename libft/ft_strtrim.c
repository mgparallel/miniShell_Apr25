/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:24:52 by menwu             #+#    #+#             */
/*   Updated: 2024/10/06 21:25:47 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	if_in_set(char c, char const *set)
{
	int	m;

	m = 0;
	while (set[m] != '\0')
	{
		if (c == set[m])
			return (1);
		else
			m++;
	}
	return (0);
}

int	find_initial(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (if_in_set(s1[i], set) != 0)
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		len;
	int		i;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen((char *)s1);
	i = find_initial(s1, set);
	if (i == len)
		return (ft_strdup(""));
	while (len > 0)
	{
		if (if_in_set(s1[len - 1], set) != 0)
			len--;
		else
			break ;
	}
	if (len < i)
		return (NULL);
	result = (char *)malloc((len - i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)s1 + i, len - i + 1);
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	char	x[] = "ab/today/abbab"; //today
	char	y[] = "ab";

	char *result = ft_strtrim(x, y);
	printf("%s", result);
	free (result);
	return (0);
}
*/
