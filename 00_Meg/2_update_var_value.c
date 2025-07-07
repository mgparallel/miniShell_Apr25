/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_update_var_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 07:20:51 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 07:21:54 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_line(char **line, t_files **lst)
{
	t_files	*temp;
	char	*new_line;

	temp = *lst;
	new_line = NULL;
	while (temp)
	{
		new_line = ft_strjoin_free(new_line, temp->value,
				ft_strlen(temp->value));
		temp = temp->next;
	}
	free_lst(lst);
	free(*line);
	*line = new_line;
}

void	update_var_value(char **var, t_files *env, t_files **lst)
{
	char	*var_value;

	var_value = get_var_value(*var, env);
	free(*var);
	if (!var_value)
		return ;
	else
		add_expanded_var_to_lst(var_value, lst);
	free(var_value);
}
