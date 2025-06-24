#include "../minishell.h"

void    set_env_var(char *var, char *path, t_files **env)
{
    char *new;

    new = ft_strjoin(var, path);
    if (!new)
        return ;
    cmd_export(new, env);
	
}

int		cd_home(t_files **env)
{
		char *str;
		char *cur_dir;
		char new_buf[1024];

		cur_dir = NULL;
		str = get_var_value("HOME", *env);
		if (!str)
		{
			printf("No $Home set\n");
			return (1);
		}
		cur_dir = get_var_value("PWD", *env);
		if (chdir(str) != 0) //when changing dir fail
			return (printf("No such file or directory\n"), 1);
		if (cur_dir)
			set_env_var("OLDPWD=", cur_dir, env);
		else
			cmd_unset("OLDPWD", env);
		if (getcwd(new_buf, sizeof(new_buf)) == NULL)
			return (printf("error after change directory\n"), 1);
		else
			set_env_var("PWD=", new_buf, env);
		printf("hrer\n");
		return (0);
}

int    cmd_cd(char *str, t_files **env)
{
    char new_buf[1024];
    char *cur_dir;
	char *temp;

	temp = NULL;
	if (!str || str[0] == '\0')
		return (cd_home(env));
	if (!ft_strcmp(str, "-"))
	{
		str = get_var_value("OLDPWD", *env);
		if (!str)
			return (printf("No such file or directory\n"), 1);
	}
    cur_dir = get_var_value("PWD", *env);
    if (chdir(str) != 0) //when changing dir fail
        return (printf("No such file or directory\n"), 1);
    if (cur_dir)
        set_env_var("OLDPWD=", cur_dir, env);
    else
        cmd_unset("OLDPWD", env);
    if (getcwd(new_buf, sizeof(new_buf)) == NULL)
        return (printf("error after change directory\n"), 1);
    else
        set_env_var("PWD=", new_buf, env);
    return (0);
}

// int main(int ac, char **ag, char **envp)
// {
//     (void)ac;
//     (void)ag;
//     t_files *env = cp_env(envp);
//     cmd_cd("./03_builtin", &env);
//     cmd_pwd(env);
//     return 0;
// }