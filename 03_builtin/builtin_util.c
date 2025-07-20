/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:25:09 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 08:25:38 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (src[i] && i < len)
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	lstadd_start(t_files **env, char *str)
{
	t_files	*temp;
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (!new)
		return ;
	new->value = ft_strdup(str);
	if (!new->value)
	{
		free(new);
		return ;
	}
	temp = *env;
	*env = new;
	new->next = temp;
}
