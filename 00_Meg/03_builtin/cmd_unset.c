/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:34:24 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 17:05:24 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			{
				*env = temp;
				return (0);
			}
			prev->next = temp;
			free(ref->value);
			free(ref);
			return (0);
		}
		prev = ref;
		ref = ref->next;
	}
	return (0);
}
