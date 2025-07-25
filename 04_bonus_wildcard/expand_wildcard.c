/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:49:24 by menwu             #+#    #+#             */
/*   Updated: 2025/07/19 16:53:03 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	indir_lst_addback(t_files **lst, t_files *new)
{
	t_files	*ref;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ref = *lst;
	while (ref && ref->next)
		ref = ref->next;
	ref->next = new;
}

void	update_result(char *value, t_files **result, int *flag)
{
	t_files	*new;

	if (*flag == 0 || *flag == -1)
		return ;
	new = malloc(sizeof(t_files));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new));
	new->next = NULL;
	*flag = 0;
	indir_lst_addback(result, new);
}

void	if_end_to_match(char **arr, int *flag)
{
	char	**ref;
	char	*prev;

	ref = arr;
	prev = NULL;
	while (*ref)
	{
		prev = *ref;
		ref++;
	}
	if (prev && !ft_strchr(prev, '*'))
		*flag = -1;
}

int	expand_wildcard(t_token **lst, t_token **cur_token)
{
	t_files	*fn_lst;
	t_files	*result;

	fn_lst = NULL;
	result = NULL;
	init_fn_lst(&fn_lst);
	if (!fn_lst)
		return (printf("Failed fetching file names\n"), -1);
	fn_match(fn_lst, (*cur_token)->value, &result);
	free_lst(&fn_lst);
	if (!result)
	{
		(*cur_token)->type = WORD;
		return (0);
	}
	add_wildcard_token(lst, *cur_token, result);
	return (0);
}
