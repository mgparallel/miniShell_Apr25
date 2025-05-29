/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:05:52 by gapujol-          #+#    #+#             */
/*   Updated: 2025/05/15 20:10:50 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirect_input_from_file(char *filename)
{
	int	fd;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("open:"), 1);
	if (dup2(fd, 0) == -1)
		return (close(fd), perror("dup2:"), 1);
	close(fd);
	return (0);
}

int	redirect_output_to_file(char *filename, int append)
{
	int	fd;
	
	if (append)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open:"), 1);
	if (dup2(fd, 1) == -1)
		return (close(fd), perror("dup2:"), 1);
	close(fd);
	return (0);
}

int	redirect_stdio(t_cmd *cmd, int prev_pipe[2], int curr_pipe[2])
{
	if (cmd->infile)
	{
		if (redirect_input_from_file(cmd->infile))
			return (1);
	}
	else if (prev_pipe[0] != -1)
		if (dup2(prev_pipe[0], 0) == -1)
			return (perror("dup2:"), 1);
	if (cmd->outfile)
	{
		if (redirect_output_to_file(cmd->outfile, cmd->append))
			return (1);
	}
	else if (curr_pipe[1] != -1)
		if (dup2(curr_pipe[1], 1) == -1)
			return (perror("dup2:"), 1);
	return (0);
}

void close_pipes(int prev[2], int curr[2])
{
	if (prev[0] != -1)
		close(prev[0]);
	if (prev[1] != -1)
		close(prev[1]);
	if (curr[0] != -1)
		close(curr[0]);
	if (curr[1] != -1)
		close(curr[1]);
}

int	heredoc(t_cmd *cmd)
{
	int		pipe_hd[2];
	char	*line;

	if (pipe(pipe_hd) == -1)
		return (perror("pipe:"), 1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			close(pipe_hd[0]);
			close(pipe_hd[1]);
			return (1);	//imprimir error de ctrl+D
		}
		if (ft_strcmp(line, cmd->infile) == 10)
			break ;
		write(pipe_hd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipe_hd[1]);
	free(cmd->infile);
	cmd->infile = NULL;
	return (pipe_hd[0]);
}

int	child_process(t_exec_data *data, t_cmd *cmd, t_files *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork:"), 1);
	if (pid == 0)
	{
		if (redirect_stdio(cmd, data->prev_pipe, data->curr_pipe))
		{
			close_pipes(data->prev_pipe, data->curr_pipe);
			exit(1);
		}
		close_pipes(data->prev_pipe, data->curr_pipe);
		exec_command(cmd, env);
		exit(127);
	}
	data->pid[data->num_pids++] = pid;
	return (0);
}

int	exec_commands(t_cmd *cmds, t_files *env)
{
	t_cmd	*cmd;
	t_exec_data	data;
	
	cmd = cmds;
	data.last_exit = 0;
	data.prev_pipe[0] = -1;
	data.prev_pipe[1] = -1;
	data.num_pids = 0;
	while (cmd)
	{
		if (ft_strncmp(cmd->argv[0], "exit", 4) == 0)
			clean_exit(cmds, env, &data);
		data.curr_pipe[0] = -1;
		data.curr_pipe[1] = -1;
		if (cmd->connector == PIPE)
		{
			if (pipe(data.curr_pipe) == -1)
			{
				while (cmd && cmd->connector == PIPE)
					cmd = cmd->next;
				perror("pipe:");
				wait_for_children(&data, &cmd);
				reset_exec_state(env, &data);
				continue ;
			}
		}
		if (cmd->heredoc)
		{
			data.prev_pipe[0] = heredoc(cmd);
			if (data.prev_pipe[0] == 1)
			{
				while (cmd && cmd->connector == PIPE)
					cmd = cmd->next;
				wait_for_children(&data, &cmd);
				reset_exec_state(env, &data);
				continue ;
			}
		}
		if (is_builtin(cmd))
			exec_builtin(cmd, env, &data);
		else
		{
			if (child_process(&data, cmd, env))
			{
				while (cmd && cmd->connector == PIPE)
					cmd = cmd->next;
				wait_for_children(&data, &cmd);
				reset_exec_state(env, &data);
			}
		}
		close(data.prev_pipe[0]);
		close(data.prev_pipe[1]);
		data.prev_pipe[0] = data.curr_pipe[0];
		data.prev_pipe[1] = data.curr_pipe[1];
		if (cmd->connector != PIPE)
		{
			int status;
			int	i;

			i = -1;
			while (++i < data.num_pids)
				waitpid(data.pid[i], &status, 0);
			if (data.num_pids)
				data.last_exit = WEXITSTATUS(status);
			while (cmd->next && (
				(cmd->connector == AND && data.last_exit != 0) ||
				(cmd->connector == OR && data.last_exit == 0)))
				cmd = cmd->next;
			data.num_pids = 0;
		}
		update_exit_status(env, data.last_exit);
		cmd = cmd->next;
	}
}
