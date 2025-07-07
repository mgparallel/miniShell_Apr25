/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:52:35 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 09:03:05 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quote_in_var(char *pos)
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
int	declare_env(t_files *env)
{
	t_files	*temp;

	temp = env;
	if (!temp)
		return (printf("no ENV data"), 1);
	while (temp->next)
	{
		printf("declare -x ");
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (0);
}

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

int invalid_var_util(char *str, char *pos)
{
    int flag;
    int i;

    flag = 0;
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
			printf("export: `%s': not a valid identifier\n", str);
			return (-1);
		}
		if (str[i] >= 48 && str[i] <= 57) //have to change here, if start with number, not valid
			flag++;
		i++;
	}
    return (flag);
}

int	invalid_var(char *str, char *pos)
{
	int	i;
    int flag;

	i = 0;
    flag = 0;
	if (!pos)
	{
		while (if_alnum_underscore_braces(str[i]))
			i++;
		if (str[i] != '\0' || all_number(str))
			return (printf("export: `%s': not a valid identifier\n", str), 1);
		else
			return (1);
	}
    flag = invalid_var_util(str, pos);
    if (flag == -1)
        return (1);
	else if (flag == pos - str)
		return (printf("export: `%s': not a valid identifier\n", str), 1);
	return (0);
}
int	if_append_var(char *str, char *pos, t_files **env)
{
	int		i;
	t_files	*curr;
	char	*prev_str;
	char	*new_str;

	i = 0;
	prev_str = NULL;
	new_str = NULL;
	curr = *env;
	while (str[i] && str + i != pos)
		i++;
	if (str[i - 1] != '+')
		return (0);
	while (curr)
	{
		if (!ft_strncmp(str, curr->value, pos - str - 1) && curr->value[pos
			- str - 1] == '=')
		{
			new_str = ft_strjoin(curr->value, pos + 1);
			if (!new_str)
				free_lst(env);
			free(curr->value);
			curr->value = new_str;
			return (1);
		}
		curr = curr->next;
	}
	prev_str = ft_strcpy(str, str + i - 1);
	if (!prev_str)
		return (2);
	new_str = ft_strjoin(prev_str, pos);
	if (!new_str)
		return (free(prev_str), 2);
	lstadd_start(env, new_str);
	return (1);
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
	{
		printf("export: `%s': not a valid identifier\n", str);
		return (2);
	}
	dequote_str = quote_in_var(pos);
	if_append = if_append_var(str, pos, env);
	if (if_append)
		return (if_append);
	new_str = cmd_export_util(dequote_str, str, pos);
	if (!new_str)
	{
		free(dequote_str);
		return (2);
	}
	if (!if_replace(new_str, env))
		lstadd_start(env, new_str);
	return (free(dequote_str), free(new_str), 0);
}
