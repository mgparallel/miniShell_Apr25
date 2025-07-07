/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fn_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:55:19 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 23:55:42 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_fn_lst(struct dirent *dp, t_files **fn_lst)
{
	t_files	*new_token;

	new_token = malloc(sizeof(t_files));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(dp->d_name);
	if (!new_token->value)
		return ;
	new_token->next = NULL;
	indir_lst_addback(fn_lst, new_token);
}

void	init_fn_lst(t_files **fn_lst)
{
	struct dirent	*dp;
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
	{
		printf("error opening directory");
		return ;
	}
	while (1)
	{
		dp = readdir(dir);
		if (dp)
			update_fn_lst(dp, fn_lst);
		else
			break ;
	}
	closedir(dir);
}
