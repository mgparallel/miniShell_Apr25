/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:09:34 by gapujol-          #+#    #+#             */
/*   Updated: 2025/06/29 20:25:27 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_numeric(const char *str)
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

int str_to_long_long(const char *str, long long *result)
{
    int sign;
	int	digit;
    unsigned long long res;

	sign = 1;
	res = 0;
    if (*str == '+')
        str++;
    else if (*str == '-')
    {
        sign = -1;
        str++;
    }
    if (!*str)
        return (0);
    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return (0);
        digit = *str - '0';
        // overflow check para unsigned long long
        if (res > (ULLONG_MAX - digit) / 10)
            return (0);
        res = res * 10 + digit;
        str++;
    }
    if (sign == -1)
    {
        if (res > (unsigned long long)LLONG_MAX + 1)
            return (0);
        *result = -(long long)res;
    }
    else
    {
        if (res > (unsigned long long)LLONG_MAX)
            return (0);
        *result = (long long)res;
    }
    return (1);
}

int cmd_exit(t_cmd *cmd_list, t_cmd *cmd, t_files **env, int last_status)
{
    long long num;

    if (cmd->argc == 1)
    {
        printf("exit\n");
		free_cmd_list(cmd_list);
		free_lst(env);
        exit(last_status);
    }
    if (!is_numeric(cmd->argv[1]))
    {
		ft_putstr_fd("exit:", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_cmd_list(cmd_list);
		free_lst(env);
        exit(2);
    }
    if (!str_to_long_long(cmd->argv[1], &num))
    {
		ft_putstr_fd("exit:", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_cmd_list(cmd_list);
		free_lst(env);
        exit(2);
    }
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
