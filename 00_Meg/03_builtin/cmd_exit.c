/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:09:34 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/16 22:19:52 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

static int	is_valid_number_body(const char *str, unsigned long long *res)
{
	int	digit;

	*res = 0;
	while (*str)
	{
		if (!isdigit((unsigned char)*str))
			return (0);
		digit = *str - '0';
		if (*res > (ULLONG_MAX - digit) / 10)
			return (0);
		*res = *res * 10 + digit;
		str++;
	}
	return (1);
}

int	str_to_long_long(const char *str, long long *result)
{
	int					sign;
	unsigned long long	res;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str || !is_valid_number_body(str, &res))
		return (0);
	if (sign == -1 && res > (unsigned long long)LLONG_MAX + 1)
		return (0);
	if (sign == 1 && res > (unsigned long long)LLONG_MAX)
		return (0);
	if (sign == -1)
		*result = -(long long)res;
	else
		*result = (long long)res;
	return (1);
}

static void	exit_with_message(t_cmd *cmd_list, t_files **env, char *arg,
		int code)
{
	ft_putstr_fd("exit:", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_cmd_list(cmd_list);
	free_lst(env);
	exit(code);
}

int	cmd_exit(t_cmd *cmd_list, t_cmd *cmd, t_files **env, int last_status)
{
	long long	num;

	if (cmd->argc == 1)
	{
		printf("exit\n");
		free_cmd_list(cmd_list);
		free_lst(env);
		exit(last_status);
	}
	if (!is_numeric(cmd->argv[1]) || !str_to_long_long(cmd->argv[1], &num))
		exit_with_message(cmd_list, env, cmd->argv[1], 2);
	if (cmd->argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	printf("exit\n");
	free_cmd_list(cmd_list);
	free_lst(env);
	exit((unsigned char)num);
}
