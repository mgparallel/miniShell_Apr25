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

char *get_var_value(char *var, t_files *env)
{
	size_t len;
	char *value;

	len = ft_strlen(var);
	while (env)
	{
		if (!ft_strncmp(env->value, var, len))
		{
			if (env->value[len] == '=')
			{	
				value = ft_strdup(env->value + (int)len + 1);
				if (!value)
					return (NULL);
				break ;
			}
		}
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (value);
}

void expand_var(t_token **lst, t_token **cur_token, t_files *env)
{
    char *original;
    char *first_part; //string before $
    char *var; //str to pass to getenv()
    char *pos;

    original = NULL;
    if ((*cur_token)->value[0] == '$')
        original = get_var_value((*cur_token)->value + 1, env);
    else
    {
        pos =  ft_strchr((*cur_token)->value, '$');
        first_part = ft_strcpy((*cur_token)->value, pos);
        if (!first_part)
            return ;
        var = ft_strdup(pos + 1);
        if (!var)
            return (free(first_part));
        if (!get_var_value(var, env))
            original = first_part;
        else
            original = ft_strjoin(first_part, get_var_value(var, env));
    }
    if (!original)
    {
        free(var);
        lst_rm_token(lst, cur_token);
    }
    (*cur_token)->value = original;
}

void parse_type_var_util(char *var, t_files *env, t_token **cur_token, t_token **lst)
{
    char *expand_value;

    expand_value = get_var_value(var, env);
    if (!expand_value)
    {
        lst_rm_token(lst, cur_token);
        return ;
    }
    else
        (*cur_token)->value = expand_value;
    (*cur_token)->type = ARG;
}

// void if_contains_var(char *pre, char* tail, t_token **curr, t_files *env)
// {
//     char *new_tail;

//     new_tail = NULL;
//     if (ft_strchr(tail, '$'))
//     {
//         new_tail = get_var_value(ft_strchr(tail, '$') + 1, env);
//         free(tail);
//         (*curr)->value = ft_strjoin(pre, new_tail);
//     }
//     else
//     {
//         (*curr)->value = ft_strjoin(pre, tail);
//     }
//     (*curr)->type = EXIT_CODE;
//     if (!(*curr)->value)
//             return ;
// }

// function to check if env_var is $?
// so it should update the type to EXIT_CODE and create new token if applicable
void    check_prev_exitcode(t_token **lst, t_token **cur_token, t_files *env)
{
        t_token *curr;
        char *pre_value;
        char *tail_value;

        pre_value = NULL;
        tail_value = NULL;
        (void)env;
        if ((*cur_token)->has_leading_space != 0 || *cur_token == *lst)
            return ;
        curr = *lst;
        while (curr->next != *cur_token)
            curr = curr->next;
        pre_value = ft_strdup(curr->value);
        if (!pre_value)
            return ;
        tail_value = ft_strdup((*cur_token)->value);
        lst_rm_token(lst, cur_token);
        free(curr->value);
        // if_contains_var(pre_value, tail_value, &curr, env);
        curr->value = ft_strjoin(pre_value, tail_value);
        curr->type = EXIT_CODE;
        if (!curr->value)
            return ;
}

int if_exit_code(t_token **lst, t_token **cur_token, t_files *env)//$?Uthat
{
    char *var;

    var = (*cur_token)->value + 1; //?that
    if_braces(&var);
    if (!ft_strchr(var, '?'))
        return (0);
    if (var[0] == '?') //that
    {
        (*cur_token)->type = EXIT_CODE;
        check_prev_exitcode(lst, cur_token, env);
        return (1);
    }
    return (0);
}

// function to check if ENV_VAR are valid
void parse_type_var(t_token **lst, t_token **cur_token, t_files *env)
{
    char *var;
    char *pos; //pointer where var ends as finding NOT-{0-9a-zA-Z_}

    if (if_exit_code(lst, cur_token, env))
        return ;
    pos = (*cur_token)->value + 1; //pos = {USER}
    while (if_alnum_underscore_braces(*pos))
    {
        if (*pos == '}')
            break ;
        pos++;
    }
    if (*pos != '\0') //we seperate into 2 tokens: VAR and ARG
    {
        if (*pos == '}')
            update_token(cur_token, (*cur_token)->value, pos + 1, ARG);
        else
            update_token(cur_token, (*cur_token)->value, pos, ARG);
        var = (*cur_token)->value + 1;
    }
    else
    {
		var = ft_strdup((*cur_token)->value + 1);
		if (!var)
        	return ;
	}
    if_braces(&var);
    parse_type_var_util(var, env, cur_token, lst);
}