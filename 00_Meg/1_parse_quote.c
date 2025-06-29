#include "minishell.h"

// funtion to remove quotes wihin the token->value
void remove_inner_quote(t_token **cur_token, char quote) //a'a'  aa
{
    char *original;
    char *new_value;
	int len;
	int i;

    original = (*cur_token)->value;
	len = ft_strlen(original);
	new_value = malloc(len - 1);
	if (!new_value)
		return ;
	len = 0;
	i = 0;
	while (original[len])
	{
		if (original[len] != quote)
		{	
			new_value[i] = original[len];
			i++;
		}
		len++;
	}
	new_value[i] = '\0';
	free(original);
	(*cur_token)->value = new_value;
	(*cur_token)->type = ARG;
}

// funtion to check if single quote/double quote contains $
// remove outer quotes and deceide if expand
void parse_type_quote(t_token **cur_token)
{
    char *dollar_pos;
    char *end_quote;

    if ((*cur_token)->type == DOUBLE_QUOTE)
    {
        end_quote = ft_strrchr((*cur_token)->value, '"');
        if (end_quote[1] != '\0')
            update_token(cur_token, (*cur_token)->value, end_quote + 1, WORD);
        remove_inner_quote(cur_token, '"');
        dollar_pos = ft_strchr((*cur_token)->value, '$');
		if (!dollar_pos)
			return ;
        // if (dollar_pos[1] && dollar_pos[1] == '{')
        (*cur_token)->type = ENV_VAR;
        return ;
        // else
        //     expand_var_quotes(lst, cur_token, env);
		return ;
    }
    else if ((*cur_token)->type == SINGLE_QUOTE)
    {
        end_quote = ft_strrchr((*cur_token)->value, '\'');
        if (end_quote[1] != '\0')
            update_token(cur_token, (*cur_token)->value, end_quote + 1, WORD);
    }
    remove_inner_quote(cur_token, '\'');
}