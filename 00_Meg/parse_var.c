#include "minishell.h"

void if_braces(char **var)
{
    char *pos;

    pos = NULL;
    if (*var[0] == '{')
    {
        pos = ft_strchr(*var, '}');
        if (!pos)
            return ;
        else if (*(pos + 1) == '\0')
        {
            *var = ft_strcpy(*var + 1, pos);
            if (!*var)
                return ;
        }
    }
}

int parse_type_var_util(char *var, t_files *env, t_token **cur_token, t_token **lst)
{
    char *expand_value;
    int if_space;

    if_space = 0;
    expand_value = get_var_value(var, env);
    if (!expand_value)
    {
        if_space = lst_rm_token(lst, cur_token);
        if ((*cur_token) && (*cur_token)->has_leading_space == 0)
            (*cur_token)->has_leading_space = if_space;
        return (1);
    }
    else
    {
        free((*cur_token)->value);
        (*cur_token)->value = expand_value;
    }
    (*cur_token)->type = ARG;
    return (0);
}

// void seperate_var_token(char *pos, t_token **cur_token, char **var)
// {
//     if (*pos == '}')
//         update_token(cur_token, (*cur_token)->value, pos + 1, WORD);
//     else
//         update_token(cur_token, (*cur_token)->value, pos, WORD);
//     *var = (*cur_token)->value + 1;
// }

// function to check if ENV_VAR are valid
int parse_type_var(t_token **lst, t_token **cur_token, t_files *env)
{
    //char *var;
    char *pos; //pointer where var ends as finding NOT-{0-9a-zA-Z_}

    
    if (if_exit_code(lst, cur_token))
        return (0);
    pos = (*cur_token)->value + 1; //US
	if (*pos == '\0'|| *pos == '+' || *pos == '=')
	{
		if (*cur_token && ((*cur_token)->next->type == SINGLE_QUOTE || (*cur_token)->next->type == DOUBLE_QUOTE))
		{
			lst_rm_token(lst, cur_token);
			return (1);
		}
		(*cur_token)->type = ARG;
		return (0);
	}
    // while (if_alnum_underscore_braces(*pos))
    // {
    //     if (*pos == '}')
    //         break ;
    //     pos++;
    // }
    // if (*pos != '\0') //we seperate into 2 tokens: VAR and ARG
    //     seperate_var_token(pos, cur_token, &var);
    // else
    // {
	// 	var = ft_strdup((*cur_token)->value + 1);
	// 	if (!var)
    //     	return ;
	// }
    if_braces(&pos);
    return (parse_type_var_util(pos, env, cur_token, lst));
}