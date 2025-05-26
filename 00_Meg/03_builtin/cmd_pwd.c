#include "../minishell.h"

char *cmd_pwd(t_files *env)
{
    t_files *ref;
    char *result;

    ref = env;
    result = NULL;
    while (ref)
    {
        if (!ft_strncmp(ref->value, "PWD=", 4))
        {
            result = ft_strdup(ref->value + 4);
            break ;
        }
        ref = ref->next;
    }
    return (result);
}

void    pwd_env(t_files *env)
{
    while (env->next)
    {
        printf("%s\n", env->value);
        env = env->next;
    }
}

// int main(int ac, char **ag, char **envp)
// {
//     t_files *env;
//     env = cp_env(envp);

//     char *re = cmd_pwd(env);
//     printf("re: %s\n", re);
//     // pwd_env(env);
//     return 0;
// }