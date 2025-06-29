/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_tokenize_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:18:15 by menwu             #+#    #+#             */
/*   Updated: 2025/06/30 00:18:19 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void token_left(char **token_start, int **in_token, char *input)
{
        *token_start = input;
        **in_token = 1;
}

int parse_input(char **input, t_token **head, int *in_token, char **token_start)
{
    int s_q;
    int d_q;

    s_q = 0;
    d_q = 0;
    while (**input)
    {
        if (**input == '\'' && !d_q && *in_token)
                *in_token = close_s_quote(&s_q, *input, token_start, head);
        else if (**input == '\'' && !d_q)
                quote_found(in_token, &s_q, token_start, *input);
        else if (**input == '"' && !s_q && *in_token)
                *in_token = close_d_quote(&d_q, *input, token_start, head);
        else if (**input == '"' && !s_q)
                quote_found(in_token, &d_q, token_start, *input);
        else if (!s_q && !d_q && (space_special(**input)))
        {
            if (!delimiter_found(in_token, input, token_start, head))
                continue ;
        }
        else if (!*in_token)
            token_left(token_start, &in_token, *input);
        (*input)++; 
    }
    return (*in_token);
}

// int parse_input(char **input, t_token **head, int *in_token, char **token_start)
// {
//     int single_quote;
//     int double_quote;

//     single_quote = 0;
//     double_quote = 0;
//     while (**input)
//     {
//         if (**input == '\'' && !double_quote)
//         {
//             if (*in_token)
//                 *in_token = close_s_quote(&single_quote, 
//                                 *input, token_start, head);
//             else
//                 quote_found(in_token, &single_quote, token_start, *input);
//         }
//         else if (**input == '"' && !single_quote)
//         {
//             if (*in_token)
//                 *in_token = close_d_quote(&double_quote, 
//                                 *input, token_start, head);
//             else
//                 quote_found(in_token, &double_quote, token_start, *input);
//         }
//         else if (!single_quote && !double_quote && 
//                                 (ch_is_space(**input) || ch_is_special(**input)))
//         {
//             if (!delimiter_found(in_token, input, token_start, head))
//                 continue ;
//         }
//         else
//         {
//             if (!*in_token)
//             {
//                     *token_start = *input;
//                     *in_token = 1;
//             }
//         }
//         (*input)++; 
//     }
//     return (*in_token);
// }