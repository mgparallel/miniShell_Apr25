/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_match.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:47:39 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 22:47:46 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_match(const char *big, const char *little)
{
	int	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
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
