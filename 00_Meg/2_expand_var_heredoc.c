/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_expand_var_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 06:23:10 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 07:21:37 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code_found(char ch, int exit_status, int *end, t_files **lst)
{
	char	*exit_code;

	exit_code = NULL;
	if (ch == '?')
	{
		exit_code = ft_itoa(exit_status);
		add_expanded_var_to_lst(exit_code, lst);
		free(exit_code);
		(*end)++;
		return (1);
	}
	return (0);
}

char	*substr_var(char *line, int *start, int *end, t_files **lst)
{
	char	*var;

	var = NULL;
	while (if_alnum_underscore_braces(line[*end]) == 1)
		(*end)++;
	var = ft_strndup(line + *start, *end - *start);
	if (!var)
		return (free_lst(lst), NULL);
	*start = *end;
	return (var);
}

void	expand_var_heredoc_util(char **line, int *start, int *end,
		t_files **lst)
{
	if (*end > *start)
		add_node_to_lst(*line, start, end, lst);
	update_line(line, lst);
}

void	expand_var_heredoc(char **line, int exit_status, t_files *env)
{
	t_files	*lst;
	int		start;
	int		end;
	char	*var;

	lst = NULL;
	start = 0;
	end = start;
	var = NULL;
	while ((*line)[end])
	{
		if ((*line)[end] == '$')
		{
			add_node_to_lst(*line, &start, &end, &lst);
			if (exit_code_found((*line)[end], exit_status, &end, &lst))
				continue ;
			var = substr_var(*line, &start, &end, &lst);
			if (!var)
				return ;
			update_var_value(&var, env, &lst);
		}
		else
			end++;
	}
	expand_var_heredoc_util(line, &start, &end, &lst);
}
