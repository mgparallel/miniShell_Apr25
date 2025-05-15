int	redirect_input_from_file(char *filename)
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

int	redirect_output_to_file(char *filename)
{
	int	fd;
	
	if (cmd->append)
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
		if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
			return (perror("dup2:"), 1);
	if (cmd->outfile)
	{
		if (redirect_output_to_file(cmd->outfile))
			return (1);
	}
	else if (curr_pipe[1] != -1)
		if (dup2(curr_pipe[1], STDOUT_FILENO) == -1)
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

int	exec_commands(t_cmd *cmds, t_files *env)
{
	t_cmd	*cmd;
	int 	last_exit;
	int		prev_pipe[2];
	int		curr_pipe[2];
	pid_t	pid;
	
	cmd = cmds;
	last_exit = 0;
	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	while (cmd)
	{
		curr_pipe[0] = -1;
		curr_pipe[1] = -1;
		if (cmd->connector == PIPE)
			if (pipe(curr_pipe) == -1)
				return (perror("pipe:"), 1);
		exec_builtin();
		if (cmd->heredoc)
			prev_pipe[0] = heredoc(cmd);
		pid = fork();
		if (pid == -1)
			return (perror("fork:"));
		if (pid == 0)
		{
			if (redirect_stdio(cmd, prev_pipe, curr_pipe))
				return (NULL);
			close_pipes(prev_pipe, curr_pipe);
			choose_command(cmd, env, cmds);
		}
		close_pipes(prev_pipe, {-1, -1})
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
		if (cmd->connector != PIPE)
		{
			int status;
			waitpid(pid, &status, 0);
			last_exit = WEXITSTATUS(status);
			while (cmd->next && (
				(cmd->connector == AND && last_exit != 0) ||
				(cmd->connector == OR && last_exit == 0)))
				cmd = cmd->next;
		}
		cmd = cmd->next;
	}
}
