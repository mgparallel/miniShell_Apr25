#include "minishell.h"

int if_exitcode_at_head(char *dollar_sign, t_token **cur_token)
{
    if (*dollar_sign == '?')
    {
        (*cur_token)->type = ENV_VAR;
        if (dollar_sign + 1)
            update_token(cur_token, (*cur_token)->value, dollar_sign + 1, WORD);
        return (1);
    }
    return (0);
}

void loop_var(char *pos, t_token **cur_token)
{
    char *dollar_sign;

    dollar_sign = pos + 1;
    if (if_exitcode_at_head(dollar_sign, cur_token))
        return ;
    while (if_alnum_underscore_braces(*dollar_sign) == 1)
    {
        if (*dollar_sign == '}')
            break ;
        dollar_sign++;
    }
    if (*dollar_sign != '\0') //we seperate into 2 tokens: VAR and WORD
    {
        if (*dollar_sign == '}')
            update_token(cur_token, (*cur_token)->value, dollar_sign + 1, WORD);
        else
            update_token(cur_token, (*cur_token)->value, dollar_sign, WORD);
        (*cur_token)->type = ENV_VAR;
    }
    else
        (*cur_token)->type = ENV_VAR;
}

void var_found(t_token **cur_token) //$USER$PWD
{
    char *original;
    char *pos;

    if ((*cur_token)->type == SINGLE_QUOTE || (*cur_token)->type == DOUBLE_QUOTE)
        return ;
    original = (*cur_token)->value;
    pos = ft_strchr(original, '$');
    if (!pos)
        return ;
    if (pos != original)
    {
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
    if (if_wildcard(cur_token)) //funtion return true/false
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
}