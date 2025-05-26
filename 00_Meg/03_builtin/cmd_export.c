#include "../minishell.h"

void    lstadd_start(t_files **env, char *str)
{
    t_files *temp;
    t_files *new;

    new = malloc(sizeof(t_files));
    if (!new)
        return ;
    new->value = str;
    temp = *env;
    *env = new;
    new->next = temp;
}

bool quote_found(char **pos)
{
    char *end;
    char result;

    end = *pos + (int)ft_strlen(*pos) - 1;
    if ((*pos[1] == '\'' && end[0] == '\'') || (*pos[1] == '"' && end[0] == '"'))
    {
        *pos = ft_strcpy(*pos + 2, end - 1);
        return (true);
    }
    else
        return (false);
}

void    cmd_export(char *str, t_files **env)
{
    char *pos;
    char *new;
    char *first;

    new = NULL;
    pos = ft_strchr(str, '=');
    if (!pos)
        return ;
    if (!quote_found(&pos))
    {
        lstadd_start(env, str);
        return ;
    }
    else
    {
        first = ft_strcpy(str, pos - 1);
        if (!first)
            return ;
        new = ft_strjoin(first, pos);
        free(first);
    }
    lstadd_start(env, new);
}

// int main(int ac, char **ag, char **envp)
// {
//     t_files *env;
//     env = cp_env(envp);

//     cmd_export(ag[1], &env);
//     printf("first: %s\n", env->value);
//     printf("second: %s\n", env->next->value);
//     return 0;
// }