/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:57:02 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 00:48:41 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strmatch(const char *big, const char *little)
{
	int	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	if (!big)
		return (NULL);
	printf("big: %s, little: %s\n", big, little);
	while (*big)
	{
		i = 0;
		while (big[i] && little[i] && big[i] == little[i])
		{
			i++;
			if (little[i] == '\0')
			{
				while (i--)
					big++;
				return ((char *)big);
			}
		}
		big++;
	}
	return (NULL);
}
