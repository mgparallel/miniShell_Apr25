/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:32:34 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 22:32:51 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
