#include "minishell.h"

// funtion to remove quotes outside of literal value
void remove_outer_quote(t_token **lst, t_token **cur_token)
{
    char *original;
    char *new_value;
    char *end;

    original = (*cur_token)->value;
    end = ft_strrchr(original, *original);
    new_value = ft_strcpy(original + 1, end);
    if (!new_value)
        return ;
    (*cur_token)->value = new_value;
    if_cmd(lst, cur_token);
    free(original);
}

// funtion to check if single quote/double quote contains $
// remove outer quotes and deceide if expand
void parse_type_quote(t_token **lst, t_token **cur_token)
{
    char *dollar_pos;

    dollar_pos = ft_strchr((*cur_token)->value, '$');
    if (dollar_pos && (*cur_token)->type == DOUBLE_QUOTE)
        expand_var(cur_token, dollar_pos);
    else
        remove_outer_quote(lst, cur_token);
}