/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_expand_var_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:53:12 by menwu             #+#    #+#             */
/*   Updated: 2025/07/05 00:10:13 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_var_value(char *var, t_files *env)
{
	size_t len;
	char *value;

	len = ft_strlen(var);
	while (env)
	{
		if (!ft_strncmp(env->value, var, len))
		{
			if (env->value[len] == '=')
			{	
				value = ft_strdup(env->value + (int)len + 1);
				if (!value)
					return (NULL);
				break ;
			}
		}
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (value);
}

char *update_original(t_token **cur_token, t_files *env, char **var)
{
    char *first_part;
    char *pos;

    pos =  ft_strchr((*cur_token)->value, '$');
    first_part = ft_strcpy((*cur_token)->value, pos);
    if (!first_part)
        return (NULL);
    *var = ft_strdup(pos + 1);
    if (!var)
        return (free(first_part), NULL);
    if (!get_var_value(*var, env))
        return (first_part);
    else
        return (ft_strjoin(first_part, get_var_value(*var, env)));
}

void no_original(char *var, t_token **lst, t_token **cur_token)
{
	if (var)
		free(var);
    lst_rm_token(lst, cur_token);
}

void expand_var_quotes(t_token **lst, t_token **cur_token, t_files *env)
{
    char *original;
    char *var;

    original = NULL;
    var = NULL;
    if ((*cur_token)->value[0] == '$')
	{
		if (!(*cur_token)->value[1] || (*cur_token)->value[1] == '+')
		{
			(*cur_token)->type = ARG;
			return ;
		}
		else if ((*cur_token)->value[1] == '=')
		{
			lst_rm_token(lst, cur_token);
			return ;
		}
        original = get_var_value((*cur_token)->value + 1, env);
	}
	else
        original = update_original(cur_token, env, &var);
    if (!original)
		return (no_original(var, lst, cur_token));
    (*cur_token)->value = original;
}