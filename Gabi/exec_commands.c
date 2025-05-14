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

void close_all_pipes(int prev[2], int curr[2])
{
	if (prev[0] != -1) close(prev[0]);
	if (prev[1] != -1) close(prev[1]);
	if (curr[0] != -1) close(curr[0]);
	if (curr[1] != -1) close(curr[1]);
}

void	exec_commands(t_cmd *cmds, t_files *env)
{
	t_cmd	*cmd;
	int 	last_exit;
	int prev_pipe[2];
	int curr_pipe[2];
	
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
		pid_t pid = fork();
		if (pid == -1)
			return (perror("fork:"));
		if (pid == 0) 
		{
			if (cmd->infile)
				redirect_input_from_file(cmd->infile);
			else if (prev_pipe[0] != -1)
				dup2(prev_pipe[0], STDIN_FILENO);
			if (cmd->outfile)
				redirect_output_to_file(cmd->outfile);
			else if (curr_pipe[1] != -1)
				dup2(curr_pipe[1], STDOUT_FILENO);

			// Cierra fds no usados
			close_all_pipes(prev_pipe, curr_pipe);

			// Ejecuta comando
			execvp(cmd->argv[0], cmd->argv);
			perror("execvp");
			exit(127);
		}

		// Padre: cerrar extremos ya usados
		if (prev_pipe[0] != -1)
			close(prev_pipe[0]);
		if (prev_pipe[1] != -1)
			close(prev_pipe[1]);

		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];

		// Espera si NO hay pipe siguiente
		if (cmd->next_sep != PIPE) {
			int status;
			waitpid(pid, &status, 0);
			last_exit = WEXITSTATUS(status);

			// Saltar comandos si no cumple condición de AND / OR
			while (cmd->next && (
				(cmd->next_sep == AND && last_exit != 0) ||
				(cmd->next_sep == OR && last_exit == 0)))
				cmd = cmd->next;
		}

		cmd = cmd->next;
	}
}
