/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:49:56 by gapujol-          #+#    #+#             */
/*   Updated: 2025/03/12 16:55:29 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

static char	*find_command_path(char *env_path, char *cmd)
{
	int		i;
	char	*full_path;
	char	**paths;

	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (!full_path || access(full_path, X_OK) == 0)
			return (free_arr(paths), full_path);
		free(full_path);
	}
	free_arr(paths);
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	*path_env;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	i = -1;
	path_env = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
	}
	if (!path_env)
		return (NULL);
	return (find_command_path(path_env, cmd));
}

char	**lst_to_envp(t_files *env)
{
    int		count;
	int		i;
    t_files	*tmp;
    char	**envp;

	tmp = env;
	count = 0;
    while (tmp && ++count)
        tmp = tmp->next;
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL);
    tmp = env;
	i = -1;
    while (++i < count)
    {
        envp[i] = ft_strdup(tmp->value);
        if (!envp[i])
        {
            while (--i >= 0)
                free(envp[i]);
            return (free(envp), NULL);
        }
        tmp = tmp->next;
    }
    envp[count] = NULL;
    return (envp);
}

void	exec_command(char **cmd_args, t_files *env)
{
	char	**envp;
	char	*cmd_path;

	envp = lst_to_envp(env);
	free_lst(env);
	if (!envp)
		exit(1);
	cmd_path = get_command_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd_args[0], stderr);
		ft_putstr_fd(": command not found \n", stderr);
		exit(127);
	}
	signal(SIGINT, SIG_DFL);
	execve(cmd_path, cmd_args, envp);
	perror("execve");
	free(cmd_path);
	free_arr(envp);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}
