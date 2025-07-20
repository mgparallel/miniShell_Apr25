/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_copy_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:18:39 by menwu             #+#    #+#             */
/*   Updated: 2025/07/06 22:34:18 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst(t_files **lst)
{
	t_files	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	update_env(char *value, t_files **env)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), free_lst(env));
	new->next = NULL;
	indir_lst_addback(env, new);
}

int	replace_last_cmd(char *line, t_files **env, int *i)
{
	if (!ft_strncmp(line, "_=", 2))
	{
		update_env("_=/usr/bin/env", env);
		*i += 1;
		return (1);
	}
	return (0);
}

t_files	*cp_env(char **envp)
{
	int		i;
	t_files	*env;
	char	*original;
	char	*new_value;

	i = 0;
	env = NULL;
	original = NULL;
	while (envp[i])
	{
		if (replace_last_cmd(envp[i], &env, &i))
			continue ;
		update_env(envp[i], &env);
		if (!ft_strncmp(envp[i], "PWD=", 4))
			original = envp[i];
		i++;
	}
	new_value = ft_strjoin("OLD", original);
	if (!new_value)
		return (free_lst(&env), NULL);
	update_env(new_value, &env);
	free(new_value);
	return (env);
}
