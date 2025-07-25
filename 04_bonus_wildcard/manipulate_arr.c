/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:00:42 by menwu             #+#    #+#             */
/*   Updated: 2025/07/16 00:42:15 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cpy_arr(int i, int len, char **new_arr, char **arr)
{
	while (i < len)
	{
		new_arr[i + 1] = ft_strdup(arr[i]);
		if (!new_arr[i + 1])
			return (free_arr(new_arr), free_arr(arr));
		i++;
	}
	new_arr[i + 1] = NULL;
}

char	**prepend_arr_util(int len, char **arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	new_arr = NULL;
	new_arr = (char **)malloc(sizeof(char *) * (len + 3));
	if (!new_arr)
		return (NULL);
	new_arr[i] = ft_strdup("*");
	if (!new_arr[i])
		return (free_arr(new_arr), free_arr(arr), NULL);
	cpy_arr(i, len, new_arr, arr);
	new_arr[i + 2] = NULL;
	return (new_arr);
}

char	**prepend_arr(char **arr, char *value)
{
	char	**new_arr;
	int		len;
	int		i;

	len = 0;
	i = 0;
	new_arr = NULL;
	while (arr[len])
		len++;
	if (value[ft_strlen(value) - 1] == '*')
	{
		new_arr = prepend_arr_util(len, arr);
		return (new_arr);
	}
	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	new_arr[i] = ft_strdup("*");
	if (!new_arr[i])
		return (free_arr(new_arr), free_arr(arr), NULL);
	cpy_arr(i, len, new_arr, arr);
	return (new_arr);
}

char	**append_arr(char **arr)
{
	char	**new_arr;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (arr[len])
		len++;
	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			return (free(new_arr), free_arr(arr), NULL);
		i++;
	}
	new_arr[i] = ft_strdup("*");
	if (!new_arr[i])
		return (free_arr(new_arr), free_arr(arr), NULL);
	new_arr[i + 1] = NULL;
	return (new_arr);
}
