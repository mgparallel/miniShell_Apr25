/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:34:50 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 22:34:51 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_pwd(t_files *env)
{
	t_files	*ref;
	char	*result;

	ref = env;
	result = NULL;
	while (ref)
	{
		if (!ft_strncmp(ref->value, "PWD=", 4))
		{
			result = ft_strdup(ref->value + 4);
			break ;
		}
		ref = ref->next;
	}
	if (ref == NULL)
		return (printf("no PWD value\n"), 1);
	printf("%s\n", result);
	free(result);
	return (0);
}

int	cmd_env(t_files *env)
{
	t_files	*temp;

	temp = env;
	if (!temp)
		return (printf("no ENV data"), 1);
	while (temp)
	{
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (0);
}
