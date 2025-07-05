/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_if_exit_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:53:45 by menwu             #+#    #+#             */
/*   Updated: 2025/07/05 10:14:25 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int if_exit_code(t_token **cur_token)
{
    char *var;

    var = (*cur_token)->value + 1;
    if (!ft_strchr(var, '?'))
        return (0);
    if (var[0] == '?')
    {
        (*cur_token)->type = EXIT_CODE;
        return (1);
    }
    return (0);
}