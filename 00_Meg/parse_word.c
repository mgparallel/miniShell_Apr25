#include "minishell.h"

int if_exitcode_at_head(char *init_var, t_token **cur_token)
{
    if (*init_var == '?')
    {
        (*cur_token)->type = ENV_VAR;
        if (init_var + 1)
            update_token(cur_token, (*cur_token)->value, init_var + 1, WORD);
        return (1);
    }
    return (0);
}

void loop_var(char *pos, t_token **cur_token)
{
    char *init_var;

    init_var = pos + 1; //US
    if (if_exitcode_at_head(init_var, cur_token) || !init_var)
        return ;
	// else if (*init_var == '=')
	// {
	// 	(*cur_token)->type = ENV_VAR;
	// 	update_token(cur_token, (*cur_token)->value, init_var + 1, WORD);
	// 	return ;
	// }
	// else if (*init_var == '\'')
	// {
	// 	(*cur_token)->type = ENV_VAR;
	// 	update_token(cur_token, (*cur_token)->value, ft_strrchr((*cur_token)->value, '\''), WORD);
	// 	return ;
	// }
    while (if_alnum_underscore_braces(*init_var) == 1)
    {
        if (*init_var == '}')
            break ;
        init_var++;
    }
    if (*init_var != '\0') //we seperate into 2 tokens: VAR and WORD
    {
        if (*init_var == '}')
            update_token(cur_token, (*cur_token)->value, init_var + 1, WORD);
        else
            update_token(cur_token, (*cur_token)->value, init_var, WORD);
        (*cur_token)->type = ENV_VAR;
    }
    else
        (*cur_token)->type = ENV_VAR;
}

void var_found(t_token **cur_token) //$USER$PWD
{
    char *original;
    char *pos;

    // printf("value: %s, type: %u\n", (*cur_token)->value, (*cur_token)->type);
    if ((*cur_token)->type == SINGLE_QUOTE || (*cur_token)->type == DOUBLE_QUOTE)
        return ;
    original = (*cur_token)->value; //$US
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
        update_token(cur_token, original, pos, WORD);
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

    original = (*cur_token)->value; //a   ''a'a'
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