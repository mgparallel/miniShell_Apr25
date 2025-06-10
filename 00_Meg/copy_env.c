#include "minishell.h"

void free_lst(t_files **lst)
{
	t_files *temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void update_env(char *value, t_files **env)
{
    t_files *new;

    new = malloc(sizeof(t_files));
    if (!new)
		return ;
    new->value = ft_strdup(value);
    if (!new->value)
        return (free(new), free_lst(env));
    new->next = NULL;
    indir_lst_addback(env, new);
}

t_files *cp_env(char **envp)
{
    int i;
	t_files *env;
	// char *exit;

	i = 0;
	env = NULL;
	// exit = "?=0";
    while (envp[i])
    {
        update_env(envp[i], &env);
		i++;
    }
	// update_env(exit, &env);
	return (env);
}