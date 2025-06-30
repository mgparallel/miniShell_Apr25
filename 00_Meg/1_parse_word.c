/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:12:22 by menwu             #+#    #+#             */
/*   Updated: 2025/07/01 00:14:24 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int if_exitcode_at_head(char *init_var, t_token **cur_token)
{
    if (*init_var == '?')
    {
        (*cur_token)->type = EXIT_CODE;
        if (init_var[1])
            update_token(cur_token, (*cur_token)->value, init_var + 1, WORD);
        return (1);
    }
    return (0);
}

void loop_var(char *pos, t_token **cur_token)
{
    char *init_var;

    init_var = pos + 1; 
    if (if_exitcode_at_head(init_var, cur_token) || !init_var)
        return ;
    while (if_alnum_underscore_braces(*init_var) == 1)
        init_var++;
    if (*init_var != '\0') //we seperate into 2 tokens: VAR and WORD
        update_token(cur_token, (*cur_token)->value, init_var, WORD);
    (*cur_token)->type = ENV_VAR;
   
}

void var_found(t_token **cur_token) //${USER}
{
    char *original;
    char *pos;

    if ((*cur_token)->type == SINGLE_QUOTE || (*cur_token)->type == DOUBLE_QUOTE)
        return ;
    original = (*cur_token)->value; //$?
    pos = ft_strchr(original, '$');
    if (!pos)
        return ;
	else if (!pos[1] && !(*cur_token)->next)
	{
		(*cur_token)->type = ARG;
		return ;
	}
    if (pos != original)
    {
        (*cur_token)->type = ARG;
        update_token(cur_token, original, pos, ENV_VAR);
        return ;
    }
    loop_var(pos, cur_token);
}

// funton to parse the token with type="WORD"
// if find quotes, remove and update token value
void parse_type_word(t_token **cur_token)
{
    char *original;
    char *s_quote_pos;
    char *d_quote_pos;

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
    var_found(cur_token);
}