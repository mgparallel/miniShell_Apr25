#include "minishell.h"

 int var_found(t_token **cur_token)
{
    char *original;
    char *pos;

    original = (*cur_token)->value;
    pos = ft_strchr(original, '$');
    if (!pos)
        return (0);
    if (pos == original)
    {
        (*cur_token)->type = ENV_VAR;
        return (0);
    }
    else
        update_token(cur_token, original, pos, ENV_VAR);
    return (1);
}

// funton to parse the token with type="WORD"
// if find quotes, remove and update token value
void parse_type_word(t_token **lst, t_token **cur_token)
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
        var_found(cur_token);
        if_cmd(lst, cur_token);
        return ;
    }
    if (s_quote_pos && (!d_quote_pos || s_quote_pos < d_quote_pos))
    {
        if (*(ft_strrchr(original, '\'') + 1) != '\0')
        {
            printf("Quote not closed\n");
            return ; //should have a error exit
        }
        update_token(cur_token, original, s_quote_pos, SINGLE_QUOTE);
    }
    else
    {
        if (*(ft_strrchr(original, '"') + 1) != '\0')
        {
            printf("Quote not closed\n");
            return ; //should have a error exit
        }   
        update_token(cur_token, original, d_quote_pos, DOUBLE_QUOTE);
    }
    if_cmd(lst, cur_token);
}