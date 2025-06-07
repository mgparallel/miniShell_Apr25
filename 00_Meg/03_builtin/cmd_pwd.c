#include "../minishell.h"

int cmd_pwd(t_files *env)
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
    if (ref == NULL)
        return (printf("no PWD value\n"), 1);
    printf("%s\n", result);
    return (0);
}

int cmd_env(t_files *env)
{
	if (!env)
		return (printf("no ENV data"), 1);
    while (env->next)
    {
        printf("%s\n", env->value);
        env = env->next;
    }
    return (0);
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