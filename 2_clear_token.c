/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_clear_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:01:16 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 08:01:19 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		if (!*token)
			return ;
		if ((*token)->value)
			free((*token)->value);
		free(*token);
		*token = tmp;
	}
}
