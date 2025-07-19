/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:52:10 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/19 17:14:54 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_cmd *cmd);

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*next;

	if (cmd->argv)
	{
		i = -1;
		while (++i < cmd->argc)
			free(cmd->argv[i]);
		free(cmd->argv);
	}
	if (cmd->expand)
		free(cmd->expand);
	while (cmd->redir_list)
	{
		next = cmd->redir_list->next;
		free(cmd->redir_list->filename);
		free(cmd->redir_list);
		cmd->redir_list = next;
	}
	free(cmd);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		free_cmd(cmd);
		cmd = next;
	}
}

int	is_connector(t_token_type type)
{
	return (type == PIPE || type == AND || type == OR);
}

int	add_redir(t_redir **head, t_redir_type type, char *filename, int in_quote)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (1);
	new->type = type;
	new->filename = ft_strdup(filename);
	if (!new->filename)
		return (free(new), 1);
	new->in_quote = in_quote;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (0);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

t_redir_type	token_to_redir_type(const char *op)
{
	if (!ft_strcmp(op, "<"))
		return (REDIR_INPUT);
	if (!ft_strcmp(op, ">"))
		return (REDIR_OUTPUT);
	if (!ft_strcmp(op, ">>"))
		return (REDIR_APPEND);
	if (!ft_strcmp(op, "<<"))
		return (REDIR_HEREDOC);
	return (-1);
}

int	manage_redirect(t_token **t, t_cmd *cmd)
{
	t_token			*redir_token;
	t_redir_type	type;

	redir_token = *t;
	*t = (*t)->next;
	if (*t && ((*t)->type == RE_TARGET || (*t)->type == EXIT_CODE))
	{
		type = token_to_redir_type(redir_token->value);
		if (add_redir(&(cmd->redir_list), type, (*t)->value, (*t)->in_quote))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	build_arg_array(t_token *t, t_cmd *cmd)
{
	int	i;

	cmd->argc++;
	cmd->argv = ft_calloc((cmd->argc + 1), sizeof(char *));
	if (!cmd->argv)
		return (1);
	cmd->expand = ft_calloc(cmd->argc + 1, sizeof(int));
	if (!cmd->expand)
		return (free(cmd->argv), 1);
	i = 0;
	while (i < cmd->argc)
	{
		if (t->type == CMD || t->type == ARG || t->type == EXIT_CODE)
		{
			if (t->type == EXIT_CODE || (t->type == CMD && t->in_quote != 1))
				cmd->expand[i] = 1;
			cmd->argv[i] = ft_strdup(t->value);
			if (!cmd->argv[i])
				return (free_arr(cmd->argv), free(cmd->expand), 1);
			i++;
		}
		t = t->next;
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
		else if ((*tokens)->type == ARG || (*tokens)->type == EXIT_CODE)
			cmd->argc++;
		else if ((*tokens)->type == REDIRECT)
			if (manage_redirect(tokens, cmd))
				return (free_cmd(cmd), NULL);
		*tokens = (*tokens)->next;
	}
	if (cmd_token && build_arg_array(cmd_token, cmd))
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

	head = NULL;
	tail = NULL;
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
