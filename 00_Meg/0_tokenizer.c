/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:20:58 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 16:47:38 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_special_t(char **start, char **input, t_token **head, int *in_token)
{
	if (ch_is_special(**input))
	{
		*start = *input;
		if (*(*input + 1) == **input)
		{
			if (**input == '|')
				create_token(start, *input + 2, OR, head);
			else if (**input == '&')
				create_token(start, *input + 2, AND, head);
			else
				create_token(start, *input + 2, REDIRECT, head);
			*input += 2;
			return (0);
		}
		else
		{
			if (**input == '|')
				create_token(start, *input + 1, PIPE, head);
			else if (**input == '<' || **input == '>')
				create_token(start, *input + 1, REDIRECT, head);
			else
				*in_token = !*in_token;
		}
	}
	return (1);
}

int	delimiter_found(int *in_token, char **input, char **token_start,
		t_token **head)
{
	if (*in_token)
	{
		if (ch_is_space(**input))
		{
			create_token(token_start, *input, WORD, head);
			*in_token = !*in_token;
		}
		else
		{
			create_token(token_start, *input, WORD, head);
			*in_token = !*in_token;
			return (0);
		}
	}
	else if (!start_special_t(token_start, input, head, in_token))
		return (0);
	return (1);
}

int	check_quote_error(char *input)
{
	int	i;
	int	s_q;
	int	d_q;

	i = 0;
	s_q = 0;
	d_q = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !d_q)
			s_q = !s_q;
		else if (input[i] == '"' && !s_q)
			d_q = !d_q;
		i++;
	}
	if (input[i - 1] == '|' || input[i - 1] == '&')
		return (printf("syntax error near unexpected token"), 1);
	if (s_q == 0 && d_q == 0)
		return (0);
	else
		return (printf("Syntax error: Unclosed quotes/symbols"), 1);
}

t_token	*tokenizer(char *input)
{
	int		in_token;
	char	*token_start;
	t_token	*head;

	in_token = 0;
	token_start = NULL;
	head = NULL;
	if (check_quote_error(input))
		return (NULL);
	in_token = parse_input(&input, &head, &in_token, &token_start);
	if (in_token)
		create_token(&token_start, input, WORD, &head);
	return (head);
}
