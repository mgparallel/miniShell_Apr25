/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_get_var_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:53:12 by menwu             #+#    #+#             */
/*   Updated: 2025/07/16 20:30:31 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *var, t_files *env)
{
	size_t	len;
	char	*value;

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
