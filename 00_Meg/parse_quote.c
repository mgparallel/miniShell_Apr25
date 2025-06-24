#include "minishell.h"

// funtion to remove quotes outside of literal value
void remove_outer_quote(t_token **cur_token)
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
    (*cur_token)->type = ARG;
    free(original);
}

// funtion to check if single quote/double quote contains $
// remove outer quotes and deceide if expand
void parse_type_quote(t_token **lst, t_token **cur_token, t_files *env)
{
    char *dollar_pos;
    char *end_quote;

    if ((*cur_token)->type == DOUBLE_QUOTE)
    {
        end_quote = ft_strrchr((*cur_token)->value, '"');
        if (end_quote[1] != '\0')
            update_token(cur_token, (*cur_token)->value, end_quote + 1, WORD);
        remove_outer_quote(cur_token);
        dollar_pos = ft_strchr((*cur_token)->value, '$');
		if (!dollar_pos)
			return ;
        if (dollar_pos[1] && dollar_pos[1] == '{')
            (*cur_token)->type = ENV_VAR;
        else
            expand_var_quotes(lst, cur_token, env);
		return ;
    }
    else if ((*cur_token)->type == SINGLE_QUOTE)
    {
        end_quote = ft_strrchr((*cur_token)->value, '\'');
        if (end_quote[1] != '\0')
            update_token(cur_token, (*cur_token)->value, end_quote + 1, WORD);
    }
    remove_outer_quote(cur_token);
}