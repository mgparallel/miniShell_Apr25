/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:11:42 by menwu             #+#    #+#             */
/*   Updated: 2025/07/06 23:15:56 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_type_var_util(char *var, t_files *env, t_token **cur_token,
		t_token **lst)
{
	char	*expand_value;
	int		if_space;

	if_space = 0;
	expand_value = get_var_value(var, env);
	free(var);
	if (!expand_value)
	{
		if_space = lst_rm_token(lst, cur_token);
		if ((*cur_token) && (*cur_token)->has_leading_space == 0)
			(*cur_token)->has_leading_space = if_space;
		return (1);
	}
	else
	{
		if ((*cur_token)->value)
			free((*cur_token)->value);
		(*cur_token)->value = expand_value;
	}
	(*cur_token)->type = ARG;
	return (1);
}

int	if_symbol_after_dollar(t_token **cur_token, t_token **lst)
{
	if (*cur_token && ((*cur_token)->next->type == SINGLE_QUOTE
			|| (*cur_token)->next->type == DOUBLE_QUOTE))
	{
		lst_rm_token(lst, cur_token);
		return (1);
	}
	(*cur_token)->type = ARG;
	return (0);
}

int	skip_expansion(t_token **lst, t_token **cur_token)
{
	t_token	*head;

	head = *lst;
	while (head->next && head->next != *cur_token)
		head = head->next;
	if (head->type == REDIRECT && !(ft_strncmp(head->value, "<<", 2)))
		return (1);
	return (0);
}

int	check_braces(char **pos, char **var)
{
	char	*end_brace;

	end_brace = NULL;
	if (**pos == '{')
	{
		end_brace = ft_strchr(*pos, '}');
		if (!end_brace)
			return (printf("Syntex error: Non closing braces"), -1);
		*var = ft_strcpy(*pos + 1, end_brace);
		if (!*var)
			return (printf("Malloc failed"), -1);
		*pos = end_brace + 1;
	}
	if (!*var)
	{
		*var = ft_strdup(*pos);
		if (!*var)
			return (printf("Malloc failed"), -1);
		while (if_alnum_underscore_braces(**pos))
			(*pos)++;
	}
	return (0);
}

int	parse_type_var(t_token **lst, t_token **cur_token, t_files *env)
{
	char	*var;
	char	*pos;

	var = NULL;
	if (if_exit_code(cur_token) || skip_expansion(lst, cur_token))
		return (0);
	pos = (*cur_token)->value + 1;
	if (*pos == '\0' || *pos == '+' || *pos == '=')
		return (if_symbol_after_dollar(cur_token, lst));
	if (check_braces(&pos, &var) == -1)
		return (-1);
	if (*pos != '\0')
	{
		if (update_token(lst, (*cur_token)->value, pos, WORD) == -1)
			return (-1);
		free(var);
		var = ft_strcpy((*cur_token)->value + 1, pos);
		if (!var)
			return (printf("Malloc failed"), -1);
	}
	return (parse_type_var_util(var, env, cur_token, lst));
}
