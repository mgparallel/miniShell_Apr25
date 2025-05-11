#include "minishell.h"

bool ch_is_space(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n');
}

bool ch_is_special(char ch)
{
    return (ch == '>' || ch == '<' || ch == '|' || ch == '&');
}

t_token *tokenizer(char *input)
{
    int in_token;
    int single_quote;
    int double_quote;
    char *token_start;
    t_token *head;

    in_token = 0;
    single_quote = 0;
    double_quote = 0;
    token_start = NULL;
    head = NULL;
    while (*input)
    {
        if (*input == '\'' && !double_quote)
        {
            if (in_token)
            {
                if (single_quote)
                {
                    create_token(&token_start, input + 1, SINGLE_QUOTE, &head);
                    in_token = !in_token;
                }
                else
                {
                    single_quote = !single_quote;
                    input++;
                    continue ;
                }
            } 
            else
            {
                token_start = input;
                in_token = !in_token;
            }
            single_quote = !single_quote;
        }
        else if (*input == '"' && !single_quote)
        {
            if (in_token)
            {
                if (double_quote)
                {
                    create_token(&token_start, input + 1, DOUBLE_QUOTE, &head);
                    in_token = !in_token;
                }
                else
                {
                    double_quote = !double_quote;
                    input++;
                    continue ;
                }
            }
            else
            {
                token_start = input;
                in_token = !in_token;
            }
            double_quote = !double_quote;
        }
        else if (!single_quote && !double_quote && (ch_is_space(*input) || ch_is_special(*input)))
        {
            if (in_token)
            {
                if (ch_is_space(*input))
                {
                    create_token(&token_start, input, WORD, &head);
                    in_token = !in_token;
                }
                else
                {
                    create_token(&token_start, input, WORD, &head);
                    in_token = !in_token;
                    continue ;
                }
            }
            else //not in_token
            {
                token_start = input;
                if (ch_is_special(*input))
                {
                    if (*(input + 1) == *input)
                    {
                        if (*input == '|')
                            create_token(&token_start, input + 2, LOGICAL_OR, &head);
                        else if (*input == '&')
                            create_token(&token_start, input + 2, LOGICAL_AND, &head);
                        else if (*input == '$')
                            create_token(&token_start, input + 2, PID, &head);
                        else
                            create_token(&token_start, input + 2, REDIRECTION, &head);
                        input += 2;
                        continue ;
                    }
                    else
                    {
                        if (*input == '|')
                            create_token(&token_start, input + 1, PIPE, &head);
                        else if (*input == '<' || *input == '>')
                            create_token(&token_start, input + 1, REDIRECTION, &head);
                        else
                            in_token = !in_token;
                        input++;
                        continue ;
                    }
                }
            }
        }
        else
        {
            if (!in_token)
            {
                token_start = input;
                in_token = 1;
            }
        }
        input++;
    }
    if (in_token)
            create_token(&token_start, input, WORD, &head);
    return (head);
}