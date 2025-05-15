/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:52:10 by gapujol-          #+#    #+#             */
/*   Updated: 2025/05/09 12:39:51 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmd_list(t_cmd_list *list)
{
    if (!list || !list->head)
    {
        printf("Lista de comandos vacía.\n");
        return;
    }

    int cmd_num = 0;
    t_cmd *cmd = list->head;

    while (cmd)
    {
        printf("=== Comando #%d ===\n", cmd_num++);
        
        // argv
        printf("argv (%d args):", cmd->argc);
        for (int i = 0; i < cmd->argc; i++)
        {
            printf(" [%s]", cmd->argv[i]);
        }
        printf("\n");

        // redirecciones
        printf("infile:   %s\n", cmd->infile ? cmd->infile : "(none)");
        printf("outfile:  %s\n", cmd->outfile ? cmd->outfile : "(none)");
        printf("append:   %s\n", cmd->append ? "yes" : "no");
        printf("heredoc:  %s\n", cmd->heredoc ? "yes" : "no");

        // conector lógico o pipe
        switch (cmd->connector)
        {
            case PIPE:
                printf("connector: PIPE\n");
                break;
            case AND:
                printf("connector: &&\n");
                break;
            case OR:
                printf("connector: ||\n");
                break;
            default:
                printf("connector: (none)\n");
                break;
        }

        printf("\n");
        cmd = cmd->next;
    }
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

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
}

void	free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd	*next;

	while (cmd_list->head)
	{
		next = cmd_list->head->next;
		free_cmd(cmd_list->head);
		cmd_list->head = next;
	}
	free(cmd_list);
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
		else if ((*tokens)->type == ARG)
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

t_cmd_list	*build_cmds(t_token *tokens)
{
	t_cmd_list	*cmd_list;
	t_cmd		*cmd;

	cmd_list = ft_calloc(1, sizeof(t_cmd_list));
	if (!cmd_list)
		return (NULL);
	while (tokens)
	{
		cmd = build_cmd(&tokens);
		if (!cmd)
			return (free_cmd_list(cmd_list), NULL);
		if (!cmd_list->head)
			cmd_list->head = cmd;
		else
			cmd_list->curr->next = cmd;
		cmd_list->curr = cmd;
		if (tokens && is_connector(tokens->type))
			tokens = tokens->next;
	}
	print_cmd_list(cmd_list);
	return (cmd_list);
}
