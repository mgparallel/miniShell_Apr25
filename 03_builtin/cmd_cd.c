/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:25:45 by menwu             #+#    #+#             */
/*   Updated: 2025/07/16 20:26:11 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_env_var(char *var, char *path, t_files **env)
{
	char	*new;

	new = ft_strjoin(var, path);
	if (!new)
		return ;
	cmd_export(new, env);
	free(new);
}

int	cd_home(t_files **env)
{
	char	*str;
	char	*cur_dir;
	char	new_buf[1024];

	cur_dir = NULL;
	str = get_var_value("HOME", *env);
	if (!str)
		return (printf("No $Home set\n"), 1);
	cur_dir = get_var_value("PWD", *env);
	if (chdir(str) != 0)
		return (printf("No such file or directory\n"), 1);
	if (cur_dir)
		set_env_var("OLDPWD=", cur_dir, env);
	else
		cmd_unset("OLDPWD", env);
	if (getcwd(new_buf, sizeof(new_buf)) == NULL)
		return (free(str), free(cur_dir),
			printf("error after change directory\n"), 1);
	else
		set_env_var("PWD=", new_buf, env);
	return (free(str), free(cur_dir), 0);
}

int	set_oldpwd(char *str, char **cur_dir, t_files **env)
{
	if (chdir(str) != 0)
		return (free(*cur_dir), printf("No such file or directory\n"), 1);
	if (*cur_dir)
		set_env_var("OLDPWD=", *cur_dir, env);
	else
		cmd_unset("OLDPWD", env);
	return (0);
}

int	go_prev_path(t_files **env)
{
	char	*cur_dir;
	char	*str;

	cur_dir = get_var_value("PWD", *env);
	str = get_var_value("OLDPWD", *env);
	if (!str)
		return (printf("OLDPWD not set\n"), 1);
	if (chdir(str) != 0)
		return (printf("No such file or directory\n"), 1);
	set_env_var("PWD=", str, env);
	set_env_var("OLDPWD=", cur_dir, env);
	printf("%s\n", str);
	free(str);
	free(cur_dir);
	return (0);
}

int	cmd_cd(char *str, t_files **env)
{
	char	new_buf[1024];
	char	*cur_dir;

	if (!str || str[0] == '\0')
		return (cd_home(env));
	if (!ft_strcmp(str, "-"))
		return (go_prev_path(env));
	cur_dir = get_var_value("PWD", *env);
	if (set_oldpwd(str, &cur_dir, env))
		return (1);
	if (getcwd(new_buf, sizeof(new_buf)) == NULL)
		return (free(cur_dir), printf("error after change directory\n"), 1);
	else
		set_env_var("PWD=", new_buf, env);
	return (free(cur_dir), 0);
}
