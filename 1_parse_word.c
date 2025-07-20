/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:12:22 by menwu             #+#    #+#             */
/*   Updated: 2025/07/06 23:25:09 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_exitcode_at_head(char *init_var, t_token **cur_token)
{
	if (*init_var == '?')
	{
		(*cur_token)->type = EXIT_CODE;
		if (init_var[1])
		{
			if (update_token(cur_token, (*cur_token)->value, init_var + 1,
					WORD) != -1)
				return (1);
			else
				return (-1);
		}
	}
	return (0);
}

int	loop_var(char *pos, t_token **cur_token)
{
	char	*init_var;
	int		flag;

	flag = 0;
	init_var = pos + 1;
	flag = if_exitcode_at_head(init_var, cur_token);
	if (flag == 1 || !init_var)
		return (0);
	else if (flag == -1)
		return (-1);
	while (if_alnum_underscore_braces(*init_var))
	{
		if (*init_var == '}')
		{
			init_var++;
			break ;
		}
		init_var++;
	}
	if (*init_var != '\0')
		return (update_token(cur_token, (*cur_token)->value, init_var, WORD));
	else
		return (0);
}

int	no_var(char *pos, t_token **cur_token)
{
	if (!pos)
		return (0);
	else if (!pos[1] && !(*cur_token)->next)
	{
		(*cur_token)->type = ARG;
		return (0);
	}
	return (1);
}

int	var_found(t_token **lst, t_token **cur_token)
{
	char	*original;
	char	*pos;

	if ((*cur_token)->type == SINGLE_QUOTE
		|| (*cur_token)->type == DOUBLE_QUOTE)
		return (0);
	else if (skip_expansion(lst, cur_token))
	{
		(*cur_token)->type = ARG;
		return (1);
	}
	original = (*cur_token)->value;
	pos = ft_strchr(original, '$');
	if (!no_var(pos, cur_token))
		return (0);
	if (pos != original)
	{
		(*cur_token)->type = ARG;
		return (update_token(cur_token, original, pos, WORD));
	}
	(*cur_token)->type = ENV_VAR;
	loop_var(pos, cur_token);
	return (0);
}

void	parse_type_word(t_token **cur_token)
{
	char	*original;
	char	*s_quote_pos;
	char	*d_quote_pos;

	original = (*cur_token)->value;
	if (if_wildcard(cur_token))
		return ;
	s_quote_pos = ft_strchr(original, '\'');
	d_quote_pos = ft_strchr(original, '"');
	if (!s_quote_pos && !d_quote_pos)
	{
		(*cur_token)->type = ARG;
		return ;
	}
	if (s_quote_pos && (!d_quote_pos || s_quote_pos < d_quote_pos))
		update_token(cur_token, original, s_quote_pos, SINGLE_QUOTE);
	else
		update_token(cur_token, original, d_quote_pos, DOUBLE_QUOTE);
	if (!ft_strchr((*cur_token)->value, '$'))
		(*cur_token)->type = ARG;
	else
		(*cur_token)->type = ENV_VAR;
}
