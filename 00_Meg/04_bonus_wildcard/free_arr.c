/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:46:59 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 17:57:33 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}


void free_fn(t_files **fn)
{
    t_files *temp;

    while (*fn)
    {
        temp = (*fn)->next;
        if ((*fn)->value)
            free((*fn)->value);
        free(*fn);
        *fn = temp;
    }
}