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
		return (1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			close(pipe_hd[0]);
			close(pipe_hd[1]);
			return (1);
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

int	child_process(int prev_pipe[2], int curr_pipe[2], t_cmd *cmd, t_files *env)
{
	pid = fork();
	if (pid == -1)
		return (perror("fork:"), 1);
	else if (pid == 0)
	{
		if (redirect_stdio(cmd, prev_pipe, curr_pipe))
			return (-1);
		close_pipes(prev_pipe, curr_pipe);
		if (exec_command(cmd, env))
			return (-1);
	}
	else
		return (pid);
	return (pid);
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
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
			clean_exit(cmds, env, &data);
		data.curr_pipe[0] = -1;
		data.curr_pipe[1] = -1;
		if (cmd->connector == PIPE)
		{
			if (pipe(data.curr_pipe) == -1)
			{
				perror("pipe:");
				while (cmd && cmd->connector == PIPE)
					cmd = cmd->next;
				cmd = cmd->next;
				clean_data(&data, env);
				continue ;
			}
		}
		if (cmd->heredoc)
		{
			data.prev_pipe[0] = heredoc(cmd);
			if (data.prev_pipe[0] == 1)
			{
				clean_data(&data, env);
				continue ;
			}
		}
		if (is_builtin(cmd))
			last_exit = exec_builtin(cmd, env);
		else
			pid[num_pids++] = child_process(prev_pipe, curr_pipe, cmd, env);
		close_pipes(prev_pipe, prev_pipe);
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
		if (cmd->connector != PIPE)
		{
			int status;
			int	i;

			i = -1;
			while (++i < num_pids)
				waitpid(pid[i], &status, 0);
			last_exit = WEXITSTATUS(status);
			while (cmd->next && (
				(cmd->connector == AND && last_exit != 0) ||
				(cmd->connector == OR && last_exit == 0)))
				cmd = cmd->next;
		}
		update_exit_status(last_exit, env);
		cmd = cmd->next;
	}
}
