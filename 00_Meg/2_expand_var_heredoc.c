#include "minishell.h"

int		exit_code_found(char ch, int exit_status, int *end, t_files **lst)
{
		char *exit_code;

		exit_code = NULL;
		if (ch == '?')
		{
			exit_code = ft_itoa(exit_status);
			add_expanded_var_to_lst(exit_code, lst);
			free(exit_code);
			(*end)++;
			return (1);
		}
		return (0);
}

void	update_line(char **line, t_files **lst)
{
	t_files *temp;
	char *new_line;
	
	temp = *lst;
	new_line = NULL;
	while (temp)
	{
		new_line = ft_strjoin_free(new_line, temp->value, ft_strlen(temp->value));
		temp = temp->next;
	}
	free_lst(lst);
	free(*line);
	*line = new_line;
}

void	update_var_value(char **var, t_files *env, t_files **lst)
{
		char *var_value;

		var_value = get_var_value(*var, env);
		free(*var);
		if (!var_value)
			return ;
		else
			add_expanded_var_to_lst(var_value, lst);
		free(var_value);
}

char	*substr_var(char *line, int *start, int *end, t_files **lst)
{
		char *var;

		var = NULL;
		while (if_alnum_underscore_braces(line[*end]) == 1)
			(*end)++;
		var = ft_strndup(line + *start, *end - *start);
		if (!var)
			return (free_lst(lst), NULL);
		*start = *end;
		return (var);
}

void	expand_var_heredoc_util(char **line, int *start, int *end, t_files **lst)
{
		if (*end > *start)
			add_node_to_lst(*line, start, end, lst);
		update_line(line, lst);
}

void	expand_var_heredoc(char **line, int exit_status, t_files *env)   //this is$USER and $PWD the end
{
	t_files *lst;
	int start;
	int end;
	char *var;

	lst = NULL;
	start = 0;
	end = start;
	var = NULL;
	while ((*line)[end])
	{
		if ((*line)[end] == '$')
		{
			add_node_to_lst(*line, &start, &end, &lst);
			if (exit_code_found((*line)[end], exit_status, &end, &lst))
			{
				start = end;
				continue ;
			}
			start = end;
			var = substr_var(*line, &start, &end, &lst);
			if (!var)
				return ;
			update_var_value(&var, env, &lst);
		}
		else
			end++;
	}
	expand_var_heredoc_util(line, &start, &end, &lst);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_files *env = cp_env(envp);
// 	char *line;
// 	int exit_status = 1;

// 	if (argc < 2)
// 		return 1;
// 	(void)argv;
// 	line = ft_strdup("$USER and $PWD$? the end");
// 	expand_var_heredoc(&line, exit_status, env);
// 	printf("%s\n", line);
// 	free_lst(&env);
// 	free(line);
// 	return 0;
// }