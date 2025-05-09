/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:52:10 by gapujol-          #+#    #+#             */
/*   Updated: 2025/05/09 12:39:51 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token	*token_dup(t_token *original)
{
	t_token	*copy;

	if (!original)
		return (NULL);
	copy = malloc(sizeof(t_token));
	if (!copy)
		return (NULL);
	copy->type = original->type;
	copy->value = strdup(original->value);
	copy->has_leading_space = original->has_leading_space;
	copy->next = NULL;
	return (copy);
}

void add_token_to_cmd(t_cmd *cmd, t_token *token)
{
	t_token *copy;
	t_token *current;
	
	copy = token_dup(token);
	if (!copy)
		return;
	if (!cmd->tokens)
	{
		cmd->tokens = copy;
		return ;
	}
	current = cmd->tokens;
	while (current->next)
		current = current->next;
	current->next = copy;
}

void	change_fds(t_cmd *cmd, t_token *tokens)
{
	t_token	*file_token;

	file_token = tokens->next;
	if (!file_token || file_token->type != RE_TARGET)
		ft_fprintf(2, "syntax error near unexpected token %s", file_token->value);
	if (strcmp(tokens->value, "<") == 0)
		cmd->fd_in = open(file_token->value, O_RDONLY);
	else if (strcmp(tokens->value, "<<") == 0)
		cmd->fd_in = heredoc(file_token->value);
	else if (strcmp(tokens->value, ">") == 0)
		cmd->fd_out = open(file_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (strcmp(tokens->value, ">>") == 0)
		cmd->fd_out = open(file_token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	tokens = file_token->next;
}

t_cmd	*build_cmd_list(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*last_cmd;
	t_cmd	*cmd;

	cmd_list = NULL;
	while (tokens)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->fd_in = 0;
		cmd->fd_out = 1;
		while (tokens && tokens->type != PIPE && tokens->type != LOGICAL_AND && tokens->type != LOGICAL_OR)
		{
			if (tokens->type == REDIRECTION)
			{
				change_fds(cmd, tokens);
				continue;
			}
			add_token_to_cmd(cmd, tokens);
			tokens = tokens->next;
		}
		if (!cmd_list)
			cmd_list = cmd;
		else
			last_cmd->next = cmd;
		last_cmd = cmd;
		if (tokens)
			tokens = tokens->next;
	}
	return (cmd_list);
}

t_cmd	*parse_cmds(t_token *tokens)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	
	cmd = build_cmd_list(tokens);
	while (cmd && cmd->next)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_fprintf(2, "pipe failed"), NULL);
		if (cmd->fd_out == 1)
			cmd->fd_out = pipe_fd[1];
		if (cmd->next->fd_in == 0)
			cmd->next->fd_in = pipe_fd[0];
		cmd = cmd->next;
	}
	return (cmd);
}