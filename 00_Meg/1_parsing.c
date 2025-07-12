/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 06:17:41 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 16:17:56 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	merge_exitcode_tokens(t_token **cur_token, t_token **next_node)
{
	char	*new_value;

	if (!cur_token || !(*cur_token) || !(*cur_token)->next)
		return (-1);
	else
		new_value = ft_strjoin((*cur_token)->value, (*cur_token)->next->value);
	if (!new_value)
		return (printf("Failed malloc\n"), -1);
	free((*cur_token)->value);
	(*cur_token)->value = new_value;
	if ((*cur_token)->next->value)
		free((*cur_token)->next->value);
	if ((*cur_token)->next)
		free((*cur_token)->next);
	(*cur_token)->next = *next_node;
	return (0);
}

int	join_exitcode_tokens(t_token **lst, t_token **cur_token)
{
	t_token	*prev;
	t_token	*next;

	if ((*cur_token)->has_leading_space)
		return (0);
	if (!(*cur_token)->next)
		return (0);
	prev = *lst;
	next = (*cur_token)->next;
	if (!next)
		return (0);
	while (prev->next && prev->next != *cur_token)
		prev = prev->next;
	return (merge_exitcode_tokens(&prev, cur_token));
}

int	parsing_util_wildcard_arg(t_token **lst, t_token **cur_token)
{
	if ((*cur_token)->type == WILDCARD)
	{
		if (expand_wildcard(lst, cur_token) == -1)
			return (-1);
	}
	if (parse_type_arg(lst, cur_token) == -1)
		return (-1);
	return (0);
}

int	parsing_util(t_token **cur_token, t_token **lst, t_files *env)
{
	int	flag;

	flag = 0;
	if ((*cur_token)->type == SINGLE_QUOTE
		|| (*cur_token)->type == DOUBLE_QUOTE)
	{
		flag = parse_type_quote(lst, cur_token);
		if (flag == -1)
			return (-1);
		else if (flag == 1)
			return (1);
	}
	if ((*cur_token)->type == ENV_VAR)
	{
		flag = parse_type_var(lst, cur_token, env);
		if (flag == -1)
			return (-1);
		else if (flag == 1)
			return (1);
	}
	if (parsing_util_wildcard_arg(lst, cur_token) == -1)
		return (-1);
	return (0);
}

int	parsing(t_token **lst, t_files *env, int *exit_status)
{
	t_token	*head;
	int		flag;

	head = *lst;
	while (head)
	{
		flag = 0;
		if (head->type == WORD)
		{
			parse_type_word(&head);
			if (var_found(lst, &head) == -1)
				return (1);
		}
		flag = parsing_util(&head, lst, env);
		if (flag == -1)
			return (1);
		else if (flag == 1)
			continue ;
		head = head->next;
	}
	if_cmd(lst);
	return (*exit_status);
}
