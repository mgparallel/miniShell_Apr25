#include "minishell.h"

void quote_found(int *in_token, int *quote, char **token_start, char *input)
{
    *token_start = input;
    *in_token = !*in_token; //0
    *quote = !*quote; //
}

int close_d_quote(int *quote, char *input, char **token_start, t_token **head)
{
    int in_token;

    in_token = 1;
    if (*quote)
    {
        create_token(token_start, input + 1, DOUBLE_QUOTE, head);
        in_token = !in_token;
    }
    else
        return (in_token);
    *quote = !*quote;
    return (in_token);
}

int close_s_quote(int *quote, char *input, char **token_start, t_token **head)
{
    int in_token;

    in_token = 1;
    if (*quote)
    {
        create_token(token_start, input + 1, SINGLE_QUOTE, head);
        in_token = !in_token;
    }
    else
	{
		*quote = !*quote;
        return (in_token);
	}
    *quote = !*quote;
    return (in_token);
}

int parse_input(char **input, t_token **head, int *in_token, char **token_start)
{
    int single_quote;
    int double_quote;

    single_quote = 0;
    double_quote = 0;
    while (**input)
    {
        if (**input == '\'' && !double_quote)
        {
            if (*in_token)
                *in_token = close_s_quote(&single_quote, *input, token_start, head);
            else
                quote_found(in_token, &single_quote, token_start, *input);
        }
        else if (**input == '"' && !single_quote)
        {
            if (*in_token)
                *in_token = close_d_quote(&double_quote, *input, token_start, head);
            else
                quote_found(in_token, &double_quote, token_start, *input);
        }
        else if (!single_quote && !double_quote && (ch_is_space(**input) || ch_is_special(**input)))
        {
            if (!delimiter_found(in_token, input, token_start, head))
                continue ;
        }
        else
        {
            if (!*in_token)
            {
                    *token_start = *input;
                    *in_token = 1;
            }
        }
        (*input)++; 
    }
    return (*in_token);
}