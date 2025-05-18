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

// function to check if env_var is $?
// so it should update the type to EXIT_CODE and create new token if applicable
int if_exit_code(t_token **lst, t_token **cur_token, t_files *env)
{
    char *var;

    var = (*cur_token)->value + 1;
    if_braces(&var);
    if (!ft_strchr(var, '?'))
        return (0);
    if (var[0] == '?')
    {
        if (ft_strlen(var) > 2)
            update_token(cur_token, (*cur_token)->value, (*cur_token)->value + 2, ARG);
        else
            parse_type_var_util("?", env, cur_token, lst);
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