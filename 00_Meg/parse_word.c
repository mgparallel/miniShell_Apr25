#include "minishell.h"

void var_found(t_token **cur_token)
{
    char *original;
    char *pos;

    if ((*cur_token)->type == SINGLE_QUOTE || (*cur_token)->type == DOUBLE_QUOTE)
        return ;
    original = (*cur_token)->value;
    pos = ft_strchr(original, '$');
    if (!pos)
        return ;
    if (pos == original)
    {
        (*cur_token)->type = ENV_VAR;
        return ;
    }
    else
        update_token(cur_token, original, pos, ENV_VAR);
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
    {
        if (*(ft_strrchr(original, '\'') + 1)  == '\0')
            update_token(cur_token, original, s_quote_pos, SINGLE_QUOTE);
    }
    else
    {
        if (*(ft_strrchr(original, '"') + 1) == '\0')
            update_token(cur_token, original, d_quote_pos, DOUBLE_QUOTE);
    }
}