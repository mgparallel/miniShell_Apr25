void	exec_commands(t_cmd *cmds)
	t_cmd	*cmd;
	int 	last_exit;
	int prev_pipe[2];
	int curr_pipe[2];
	
	cmd = cmds;
	last_exit = 0;
	prev_pipe = {-1, -1};
	while (cmd)
	{
		curr_pipe[0] = -1;
		curr_pipe[1] = -1;
		if (cmd->connector == PIPE)
		{
			if (pipe(curr_pipe) == -1)
				return ;
			
		}
		pid_t pid = fork();
		if (pid == 0) {
			// Hijo: configurar redirecciones

			// Entrada: puede venir de archivo o de pipe
			if (cmd->redir_in)
				redirect_input_from_file(cmd->redir_in);
			else if (prev_pipe[0] != -1)
				dup2(prev_pipe[0], STDIN_FILENO);

			// Salida: puede ir a archivo o a pipe
			if (cmd->redir_out)
				redirect_output_to_file(cmd->redir_out, cmd->append_out);
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
