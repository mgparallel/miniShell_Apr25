/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:34:24 by menwu             #+#    #+#             */
/*   Updated: 2025/07/19 14:00:54 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_node(t_files **ref)
{
	if (!ref || !*ref)
		return (0);
	if ((*ref)->value)
		free((*ref)->value);
	free(*ref);
	*ref = NULL;
	return (0);
}

int	cmd_unset(char *var, t_files **env)
{
	t_files	*temp;
	t_files	*prev;
	t_files	*ref;

	prev = NULL;
	ref = *env;
	while (ref)
	{
		if (!ft_strncmp(var, ref->value, ft_strlen(var))
			&& ref->value[ft_strlen(var)] == '=')
		{
			temp = ref->next;
			if (prev == NULL)
				*env = temp;
			else
				prev->next = temp;
			return (free_node(&ref));
		}
		prev = ref;
		ref = ref->next;
	}
	return (0);
}
