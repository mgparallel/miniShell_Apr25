/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 07:23:34 by menwu             #+#    #+#             */
/*   Updated: 2025/07/16 22:30:58 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token);

int	if_conector(t_token_type type, t_token **token, int *exit_status)
{
	if (type == PIPE || type == AND || type == OR)
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd((*token)->value, 2);
		ft_putstr_fd("'\n", 2);
		*exit_status = 1;
		clear_token(token);
		return (1);
	}
	return (0);
}

void	execution(t_token **token, t_files **env, int *exit_status)
{
	t_cmd	*cmds;

	cmds = build_cmds(*token);
	clear_token(token);
	exec_commands(cmds, env, exit_status);
	free_cmd_list(cmds);
}

int	prepare_execution(char *input, int *exit_status, t_files *env,
		t_token **token)
{
	*token = tokenizer(input);
	free(input);
	if (*token)
		parsing(token, env, exit_status);
	print_token(*token);
	if (!*token)
		return (1);
	if (if_conector((*token)->type, token, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_files	*env;
	char	*input;
	int		exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	env = cp_env(envp);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("Minishell> ");
		if (!input)
			return (exit_no_input(&exit_status, &env));
		add_history(input);
		if (prepare_execution(input, &exit_status, env, &token))
			continue ;
		execution(&token, &env, &exit_status);
	}
	free_lst(&env);
	rl_clear_history();
	return (exit_status);
}
