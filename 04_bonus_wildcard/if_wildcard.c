/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:50:55 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 23:51:25 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	if_wildcard(t_token **cur_token)
{
	char	*str;
	char	*pos;

	str = (*cur_token)->value;
	pos = ft_strchr(str, '*');
	if (!pos)
		return (false);
	(*cur_token)->type = WILDCARD;
	return (true);
}
