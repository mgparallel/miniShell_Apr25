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

#include "pipex.h"

static void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static char	*get_env_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	return (NULL);
}

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

	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (!full_path || access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
	}
	free_split(paths);
	return (NULL);
}

void	exec_command(char **cmd_args, char **envp)
{
	char	*env_path;
	char	*cmd_path;

	env_path = get_env_path(envp);
	cmd_path = find_command_path(env_path, cmd_args[0]);
	if (!cmd_path)
	{
		ft_putstr_fd("pipex: execve: Command not found \n", 2);
		free_split(cmd_args);
		exit(127);
	}
	execve(cmd_path, cmd_args, envp);
	perror("pipex: execve");
	free(cmd_path);
	free_split(cmd_args);
	exit(1);
}
