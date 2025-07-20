/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:52:35 by menwu             #+#    #+#             */
/*   Updated: 2025/07/20 12:53:02 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (0);
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	invalid_var_util(char *str, char *pos)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != *pos)
	{
		if (!if_alnum_underscore_braces(str[i]))
		{
			if (str[i] == '+')
			{
				i++;
				continue ;
			}
			print_error(str);
			return (-1);
		}
		if (i == 0 && str[i] >= 48 && str[i] <= 57)
			return (print_error(str), -1);
		i++;
	}
	return (0);
}

int	invalid_var(char *str, char *pos)
{
	int	i;

	i = 0;
	if (!pos)
	{
		while (if_alnum_underscore_braces(str[i]))
			i++;
		if (str[i] != '\0' || all_number(str))
			return (print_error(str), 1);
		else
			return (1);
	}
	if (invalid_var_util(str, pos) == -1)
		return (1);
	return (0);
}

char	*cmd_export_util(char *dequote_str, char *str, char *pos)
{
	char	*new_str;
	char	*first;

	first = NULL;
	if (!dequote_str)
		new_str = ft_strdup(str);
	else
	{
		first = ft_strcpy(str, pos + 1);
		if (!first)
			return (free(dequote_str), NULL);
		new_str = ft_strjoin(first, dequote_str);
		if (!new_str)
			return (free(first), NULL);
	}
	free(first);
	return (new_str);
}

int	cmd_export(char *str, t_files **env)
{
	char	*pos;
	char	*new_str;
	char	*dequote_str;
	int		if_append;

	if_append = 0;
	pos = ft_strchr(str, '=');
	if (invalid_var(str, pos) == 1)
		return (2);
	if (pos == str)
		return (print_error(str), 2);
	dequote_str = dequote_str_export(pos);
	if_append = if_append_var(str, pos, env);
	if (if_append)
		return (if_append);
	new_str = cmd_export_util(dequote_str, str, pos);
	if (!new_str)
		return (free(dequote_str), 2);
	if (!if_replace(new_str, env))
		lstadd_start(env, new_str);
	return (free(dequote_str), free(new_str), 0);
}
