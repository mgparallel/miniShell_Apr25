/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:52:10 by gapujol-          #+#    #+#             */
/*   Updated: 2025/05/29 23:12:47 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_cmd *head)
{
	int i = 0;
	t_cmd *cmd = head;

	if (!cmd)
	{
		printf("Lista de comandos vacía.\n");
		return;
	}
	while (cmd)
	{
		printf("Comando #%d:\n", i++);
		for (int j = 0; j < cmd->argc; j++)
			printf("  argv[%d] = \"%s\"\n", j, cmd->argv[j]);

		printf("  infile: %s\n", cmd->infile ? cmd->infile : "(null)");
		printf("  outfile: %s\n", cmd->outfile ? cmd->outfile : "(null)");
		printf("  append: %d\n", cmd->append);
		printf("  heredoc: %d\n", cmd->heredoc);
		printf("  connector: %d\n", cmd->connector);
		printf("\n");

		cmd = cmd->next;
	}
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*next;
	int		i;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->argv)
		{
			i = -1;
			while (++i < cmd->argc)
				free(cmd->argv[i]);
			free(cmd->argv);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
		cmd = next;
	}
}

static int	is_connector(t_token_type type)
{
	return (type == PIPE || type == AND || type == OR);
}

int	manage_redirect(t_token **tokens, t_cmd *cmd)
{
	if (!(*tokens)->next || (*tokens)->next->type != RE_TARGET)
		return (1);
	if (ft_strcmp((*tokens)->value, "<") == 0)
	{
		free(cmd->infile);
		cmd->infile = strdup((*tokens)->next->value);
		if (!cmd->infile)
			return (1);
	}
	else if (ft_strcmp((*tokens)->value, "<<") == 0)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	else
	{
		free(cmd->outfile);
		cmd->outfile = strdup((*tokens)->next->value);
		if (!cmd->outfile)
			return (1);
	}
	cmd->heredoc = !ft_strcmp((*tokens)->value, "<<");
	cmd->append = !ft_strcmp((*tokens)->value, ">>");
	*tokens = (*tokens)->next;
	return (0);
}

int	build_arg_array(t_token *cmd_token, t_cmd *cmd)
{
	int	i;

	cmd->argc++;
	cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!cmd->argv)
		return (1);
	i = 0;
	while (i < cmd->argc)
	{
		if (cmd_token->type == CMD || cmd_token->type == ARG)
		{
			cmd->argv[i] = strdup(cmd_token->value);
			if (!cmd->argv[i])
				return (1);
			i++;
		}
		cmd_token = cmd_token->next;
	}
	cmd->argv[cmd->argc] = NULL;
	return (0);
}

t_cmd	*build_cmd(t_token **tokens)
{
	t_cmd	*cmd;
	t_token	*cmd_token;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd_token = NULL;
	while (*tokens && !is_connector((*tokens)->type))
	{
		if ((*tokens)->type == CMD)
			cmd_token = *tokens;
		else if ((*tokens)->type == ARG || (*tokens)->type == EXIT_STATUS)
			cmd->argc++;
		else if ((*tokens)->type == REDIRECT)
			if (manage_redirect(tokens, cmd))
				return (free_cmd(cmd), NULL);
		*tokens = (*tokens)->next;
	}
	if (build_arg_array(cmd_token, cmd))
		return (free_cmd(cmd), NULL);
	if (*tokens)
		cmd->connector = (*tokens)->type;
	return (cmd);
}

t_cmd	*build_cmds(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*cmd;

	while (tokens)
	{
		cmd = build_cmd(&tokens);
		if (!cmd)
			return (free_cmd_list(head), NULL);
		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
		if (tokens && is_connector(tokens->type))
			tokens = tokens->next;
	}
	print_cmd_list(head);
	return (head);
}
