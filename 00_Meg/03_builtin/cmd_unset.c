#include "../minishell.h"

void    pwd_unset(char *var, t_files **env)
{
    t_files *temp;
    t_files *prev;

    while (env)
    {
        if (ft_strncmp(var, (*env)->value, ft_strlen(var)))
        {
            temp = (*env)->next;
            prev->next = temp;
            free(env);
            return ;
        }
        prev = env;
        env = (*env)->next;
    }
} //need to test