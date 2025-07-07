/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:53:41 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 22:33:29 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dequote_str_export(char *pos)
{
	char	*end;
	char	*result;
	int		len;

	end = pos + (int)ft_strlen(pos) - 1;
	len = ft_strlen(pos);
	if (len < 2)
		return (NULL);
	if ((pos[1] == '\'' && end[0] == '\'') || (pos[1] == '"' && end[0] == '"'))
	{
		result = ft_strndup(pos + 2, len - 3);
		return (result);
	}
	else
		return (NULL);
}

bool	if_replace(char *str, t_files **env)
{
	char	*pos;
	t_files	*curr;

	curr = *env;
	pos = ft_strchr(str, '=');
	if (!pos)
		return (false);
	while (curr)
	{
		if (!ft_strncmp(str, curr->value, pos - str + 1))
		{
			free(curr->value);
			curr->value = ft_strdup(str);
			if (!curr->value)
				free_lst(env);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

int	remove_plus_sign(char *str, char *pos, int i, t_files **env)
{
	char	*prev_str;
	char	*new_str;

	new_str = NULL;
	prev_str = ft_strcpy(str, str + i - 1);
	if (!prev_str)
		return (2);
	new_str = ft_strjoin(prev_str, pos);
	if (!new_str)
		return (free(prev_str), 2);
	lstadd_start(env, new_str);
	return (1);
}

int	appending_export(t_files **curr, char *pos, t_files **env)
{
	char	*new_str;

	new_str = ft_strjoin((*curr)->value, pos + 1);
	if (!new_str)
		return (free_lst(env), 2);
	free((*curr)->value);
	(*curr)->value = new_str;
	return (1);
}

int	if_append_var(char *str, char *pos, t_files **env)
{
	int		i;
	t_files	*curr;

	i = 0;
	curr = *env;
	while (str[i] && str + i != pos)
		i++;
	if (str[i - 1] != '+')
		return (0);
	while (curr)
	{
		if (!ft_strncmp(str, curr->value, pos - str - 1) && curr->value[pos
				- str - 1] == '=')
			return (appending_export(&curr, pos, env));
		curr = curr->next;
	}
	return (remove_plus_sign(str, pos, i, env));
}
