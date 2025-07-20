/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:14:27 by menwu             #+#    #+#             */
/*   Updated: 2025/07/16 22:16:10 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_in_exit_code(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	expand_exit_code_util(char *dest, const char *status_str, int len_status)
{
	ft_memcpy(dest, status_str, len_status);
	return (len_status);
}

char	*expand_exit_code(const char *str, const char *status_str)
{
	int		count;
	int		i;
	size_t	len_status;
	char	*new_str;

	i = 0;
	len_status = ft_strlen(status_str);
	count = count_in_exit_code(str);
	if (count == 0)
		return (ft_strdup(str));
	new_str = malloc(ft_strlen(str) + count * (len_status - 2) + 1);
	if (!new_str)
		return (NULL);
	while (*str)
	{
		if (*str == '$' && *(str + 1) == '?')
		{
			i += expand_exit_code_util(&new_str[i], status_str, len_status);
			str += 2;
		}
		else
			new_str[i++] = *str++;
	}
	new_str[i] = '\0';
	return (new_str);
}
