#include "../minishell.h"

int    cmd_unset(char *var, t_files **env)
{
    t_files *temp;
    t_files *prev;
    t_files *ref;

    prev = NULL;
    ref = *env;
    while (ref)
    {
        if (!ft_strncmp(var, ref->value, ft_strlen(var)) && ref->value[ft_strlen(var)] == '=')
        {
            temp = ref->next;
            if (prev == NULL)
            {
                *env = temp;
                return (0);
            }
            prev->next = temp;
            return (0);
        }
        prev = ref;
        ref = ref->next;
    }
}

// int main(int ac, char **ag,  char **envp)
// {
//     t_files *env;
//     env = cp_env(envp);

//     cmd_export("test=this", &env);
//     printf("first: %s\nsecond:%s\n", env->value, env->next->value);
//     cmd_unset("test", &env);
//     printf(">>new>>\n");
//     cmd_env(env);
//     return (0);
// }