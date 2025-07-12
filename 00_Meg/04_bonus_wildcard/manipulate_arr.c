/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:00:42 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 01:29:58 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**prepend_arr(char **arr, char *value, char *str)
{
	char	**new_arr;
	int		len;
	int		i;

	len = 0;
	i = 0;
	new_arr = NULL;
	while (arr[len])
		len++;
	new_arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_arr)
		return (NULL);
	if (value[ft_strlen(value) - 1] == '*')
		append_arr(arr, str);
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		return (free(new_arr), NULL);
	while (i < len)
	{
		new_arr[i + 1] = arr[i];
		i++;
	}
	new_arr[i + 1] = NULL;
	return (new_arr);
}

char	**append_arr(char **arr, char *str)
{
	char	**new_arr;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (arr[len])
		len++;
	new_arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_arr)
		return (NULL);
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		return (free_arr(new_arr), NULL);
	new_arr[i + 1] = NULL;
	return (new_arr);
}
