#include "minishell.h"

void add_node_to_lst(char *str, int *start, int *end, t_files **lst)
{
	t_files *new_node;
	char *node_value;
	int i;
	int j;

	i = *start;
	j = *end;
	// printf("start: %d, end: %d, str: %s\n", *start, *end, str);
	node_value = ft_strcpy(str + i, str + j - 1);
	if (!node_value)
		return ;
	new_node = malloc(sizeof(t_files));
	if (!new_node)
		return ;
	new_node->value = node_value;
	new_node->next = NULL;
	printf("var: %s\n", new_node->value);
	indir_lst_addback(lst, new_node);
	*end += 1;
	*start = *end;
}

void	add_expanded_var_to_lst(char *value, t_files **lst)
{
		t_files *new_node;

		new_node = malloc(sizeof(t_files));
		if (!new_node)
			return ;
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return ;
		new_node->next = NULL;
		indir_lst_addback(lst, new_node);
}

void	expand_var_heredoc(char **line, t_files *env)   //this is$USER and $PWD the end
{
	t_files *lst;
	int start;
	int end;
	char *var;
	char *var_value;
	char *new_line;

	lst = NULL;
	start = 0;
	end = start;
	var = NULL;
	var_value = NULL;
	new_line = NULL;
	while ((*line)[end])
	{
		if ((*line)[end] == '$')
		{
			add_node_to_lst(*line, &start, &end, &lst);
			while (if_alnum_underscore_braces((*line)[end]) == 1)
				end++;
			var = ft_strcpy(*line + start, *line + end);
			if (!var)
				return (free_lst(&lst));
			var_value = get_var_value(var, env);
			printf("var: %s, var_value: %s\n", var, var_value);
			start = end;
			free(var);
			if (!var_value)
				continue ;
			else
				add_expanded_var_to_lst(var_value, &lst);
			free(var_value);
		}
		else
			end++;
	}
	// free(*line);
	while(lst)
	{
		printf("value: %s\n", lst->value);
		lst = lst->next;
	}
	// while (lst)
	// {
	// 	new_line = ft_strjoin(new_line, lst->value);
	// 	lst = lst->next;
	// }
	// *line = ft_strdup(new_line);
	// free_lst(&lst);
}

int main(int argc, char **argv, char **envp)
{
	t_files *env = cp_env(envp);
	char *line;

	if (argc < 2)
		return 1;
	(void)argv;
	line = "this is$USER and $PWD the end";
	expand_var_heredoc(&line, env);
	//printf("%s\n", line);
	free_lst(&env);
	return 0;
}