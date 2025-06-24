/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:52:10 by gapujol-          #+#    #+#             */
/*   Updated: 2025/06/24 15:01:21 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *redir_type_to_str(t_redir_type type)
{
    switch (type)
    {
        case REDIR_INPUT:      return "<";
        case REDIR_OUTPUT:     return ">";
        case REDIR_APPEND:  return ">>";
        case REDIR_HEREDOC: return "<<";
        default:            return "UNKNOWN";
    }
}

const char *connector_to_str(t_token_type type)
{
    switch (type)
    {
        case PIPE:       return "|";
        case AND:return "&&";
        case OR: return "||";
        default:         return "END";
    }
}

void print_cmd_list(t_cmd *cmd)
{
    int i, cmd_num = 1;

    while (cmd)
    {
        printf("Comando %d:\n", cmd_num++);

        // Argumentos
        printf("  argc: %d\n", cmd->argc);
        printf("  argv: ");
        for (i = 0; i < cmd->argc; i++)
            printf("[%s] ", cmd->argv[i]);
        printf("\n");

        // Redirecciones
        if (cmd->redir_list)
        {
            t_redir *r = cmd->redir_list;
            printf("  Redirecciones:\n");
            while (r)
            {
                printf("    tipo: %s, archivo: %s\n", redir_type_to_str(r->type), r->filename);
                r = r->next;
            }
        }
        else
        {
            printf("  Redirecciones: ninguna\n");
        }

        // Conector
        printf("  Conector: %s\n", connector_to_str(cmd->connector));
        printf("\n");

        cmd = cmd->next;
    }
}

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_redir *next;

	if (cmd->argv)
	{
		i = -1;
		while (++i < cmd->argc)
			free(cmd->argv[i]);
		free(cmd->argv);
	}
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

static int	is_connector(t_token_type type)
{
	return (type == PIPE || type == AND || type == OR);
}

int	add_redir(t_redir **head, t_redir_type type, char *filename)
{
    t_redir *new;
	t_redir *tmp;

	new = malloc(sizeof(t_redir));
    if (!new)
        return (1);
    new->type = type;
    new->filename = ft_strdup(filename);
	if (!new->filename)
		return (free(new), 1);
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

t_redir_type token_to_redir_type(const char *op)
{
    if (!ft_strcmp(op, "<"))
        return REDIR_INPUT;
    if (!ft_strcmp(op, ">"))
        return REDIR_OUTPUT;
    if (!ft_strcmp(op, ">>"))
        return REDIR_APPEND;
    if (!ft_strcmp(op, "<<"))
        return REDIR_HEREDOC;
    return (-1);
}

int	manage_redirect(t_token **tokens, t_cmd *cmd)
{
	t_token	*redir_token;
	t_redir_type type;

	redir_token = *tokens;
	*tokens = (*tokens)->next;
	if (*tokens && ((*tokens)->type == RE_TARGET || (*tokens)->type == EXIT_CODE))
	{
		type = token_to_redir_type(redir_token->value);
		if (add_redir(&(cmd->redir_list), type, (*tokens)->value))
			return (1);
	}
	else
		return (1);
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
		if (cmd_token->type == CMD || cmd_token->type == ARG || cmd_token->type == EXIT_CODE)
		{
			cmd->argv[i] = ft_strdup(cmd_token->value);
			if (!cmd->argv[i])
			{
				while (i-- > 0)
					free(cmd->argv[i]);
				return (free(cmd->argv), 1);
			}
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
	if (is_connector(tokens->type))
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd(tokens->value, 2);
		return (ft_putstr_fd("'\n", 2), NULL);
	}
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
