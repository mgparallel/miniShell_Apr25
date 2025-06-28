#include "minishell.h"

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

char *update_original(t_token **cur_token, t_files *env, char **var)
{
    char *first_part; //string before $
    char *pos;

    pos =  ft_strchr((*cur_token)->value, '$');
    first_part = ft_strcpy((*cur_token)->value, pos);
    if (!first_part)
        return (NULL);
    *var = ft_strdup(pos + 1);
    if (!var)
        return (free(first_part), NULL);
    if (!get_var_value(*var, env))
        return (first_part);
    else
        return (ft_strjoin(first_part, get_var_value(*var, env)));
}

void expand_var_quotes(t_token **lst, t_token **cur_token, t_files *env)
{
    char *original;
    char *var;
    int if_space;

    original = NULL;
    if_space = 0;
    var = NULL;
    if ((*cur_token)->value[0] == '$')
	{
		if (!(*cur_token)->value[1] || (*cur_token)->value[1] == '+')
		{
			(*cur_token)->type = ARG;
			return ;
		}
		else if ((*cur_token)->value[1] == '=')
		{
			lst_rm_token(lst, cur_token);
			return ;
		}
        original = get_var_value((*cur_token)->value + 1, env);
	}
	else
        original = update_original(cur_token, env, &var);

    if (!original)
    {
        free(var);
        if_space = lst_rm_token(lst, cur_token);
        if ((*cur_token)->next->has_leading_space == 0)
            (*cur_token)->next->has_leading_space = if_space;
		return ;
    }
    (*cur_token)->value = original;
}