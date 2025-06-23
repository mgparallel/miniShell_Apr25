#include "../minishell.h"

char *quote_in_var(char *pos)
{
    char *end;
	char *result;
	int	len;

    end = pos + (int)ft_strlen(pos) - 1;
	len = ft_strlen(pos);
	if (len < 2)
		return (NULL);
    if ((pos[1] == '\'' && end[0] == '\'') || (pos[1] == '"' && end[0] == '"'))
    {
		result = ft_strndup(pos + 2, len - 2);
		return (result);
	}
    else
        return (NULL);
}

bool	if_replace(char *str, t_files **env)
{
		char *pos;
		t_files *curr;

		curr = *env;
		pos = ft_strchr(str, '=');
		if (!pos)
			return (false);
		while (curr)
		{
			if (!ft_strncmp(str, curr->value, pos - str + 1))
			{
				free(curr->value);
				curr->value = ft_strdup(str);
				if (!curr->value)
					free_lst(env);
				return (true);
			}
			curr = curr->next;
		}
		return (false);
}

char *cmd_export_util(char *dequote_str, char *str, char *pos)
{
	char *new_str;
	char *first;

	first = NULL;
	if (!dequote_str)
		new_str = ft_strdup(str);
	else
    {
		first = ft_strcpy(str, pos - 1);
        if (!first)
		{
			free(dequote_str);
            return (NULL);
		}
        new_str = ft_strjoin(first, dequote_str);
		if (!new_str)
			free(first);
    }
	return (new_str);
}

int    cmd_export(char *str, t_files **env)
{
    char *pos;
    char *new_str;
	char *dequote_str;

    pos = ft_strchr(str, '=');
    if (!pos)
		return (1); // when there is no '=', exitcode == 1
	dequote_str = quote_in_var(pos);
    new_str = cmd_export_util(dequote_str, str, pos);
	if (!new_str)
	{
		free(dequote_str);
        return (1);
	}
	if (!if_replace(new_str, env))
    	lstadd_start(env, new_str);
	free(new_str);
	return (0);
}

// int main(int ac, char **ag, char **envp)
// {
//     t_files *env;
//     env = cp_env(envp);

// 	if (ac > 2)
// 		return (1);
//     cmd_export(ag[1], &env);
// 	cmd_export("this=top", &env);
// 	cmd_env(env);
//     // printf("first: %s\n", env->value);
//     // printf("second: %s\n", env->next->value);
// 	free_lst(&env);
//     return 0;
// }