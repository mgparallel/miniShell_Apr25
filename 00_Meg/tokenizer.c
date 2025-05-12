#include "minishell.h"

int	start_special_token(char **token_start, char **input, t_token **head, int *in_token)
{
	if (ch_is_special(**input))
	{
        *token_start = *input;
		if (*(*input + 1) == **input)
		{
			if (**input == '|')
				create_token(token_start, *input + 2, OR, head);
			else if (**input == '&')
				create_token(token_start, *input + 2, AND, head);
			else if (**input == '$')
				create_token(token_start, *input + 2, PID, head);
			else
				create_token(token_start, *input + 2, REDIRECT, head);
			*input += 2;
			return (0);
		}
		else
		{
			if (**input == '|')
				create_token(token_start, *input + 1, PIPE, head);
			else if (**input == '<' || **input == '>')
				create_token(token_start, *input + 1, REDIRECT, head);
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
	else
		if (!start_special_token(token_start, input, head, in_token))
            return (0);
	return (1);
}

t_token	*tokenizer(char *input)
{
	int in_token;
	char *token_start;
	t_token *head;

	in_token = 0;
	token_start = NULL;
    head = NULL;
	in_token = parse_input(&input, &head, &in_token, &token_start);
	if (in_token)
		create_token(&token_start, input, WORD, &head);
	return (head);
}