/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:47:20 by gapujol-          #+#    #+#             */
/*   Updated: 2025/06/24 19:58:59 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
    if (!str || *str == '\0')
        return (0);
    while (*str)
    {
        if (!ft_isdigit((unsigned char)*str))
            return (0);
        str++;
    }
    return (1);
}

int	cmd_exit(t_cmd *cmd, int is_child)
{
	char	code;

	if (cmd->argc == 1)
		return (256 - is_child);
	if (cmd->argc == 2)
	{
		if (is_numeric(cmd->argv[1]))
		{
			code = ft_atoi(cmd->argv[1]);
			return (code + 256 - is_child);
		}
		else
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (258 - is_child);
		}
	}
	ft_putstr_fd("exit: too many arguments\n", 2);
	return (1);
}

int	is_builtin_without_output(t_cmd *cmd)
{
	if (!cmd->argv)
		return (1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}
int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

int exec_builtin_without_output(t_cmd *cmd, t_files **env, int is_child)
{
    int i;
    int flag;
	
	flag = 0;
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
    {
        if (cmd->argc > 2)
            return (ft_putstr_fd("cd: too many arguments", 2), 1);
        return (cmd_cd(cmd->argv[1], env));
    }
    i = 0;
    if (ft_strcmp(cmd->argv[0], "export") == 0)
    {
        if (cmd->argc == 1)
            return (declare_env(*env));
        while (++i < cmd->argc)
            if (cmd_export(cmd->argv[i], env) == 2)
                flag = 1;
    }
    if (ft_strcmp(cmd->argv[0], "unset") == 0)
        while (++i < cmd->argc)
            cmd_unset(cmd->argv[i], env);
    if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return (cmd_exit(cmd, is_child));
    return (flag);
}

int	exec_builtin(t_cmd *cmd, t_files **env, int is_child)
{
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (cmd_pwd(*env));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (cmd_env(*env));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (cmd_echo(cmd->argv + 1));
	return (exec_builtin_without_output(cmd, env, is_child));
}
