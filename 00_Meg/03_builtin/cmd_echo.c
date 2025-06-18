#include "../minishell.h"
//take into account that when echo "" is print out a new line
//when there are other cmds, it ignores.
int	cmd_echo(int argc, char **argv) //change to char **argv
{
	int	nl;

	nl = 1;
	if (argc < 1)
		return (printf("\n"), 0);
	if (ft_strncmp(*argv, "-n", 2) == 0)
	{
		nl = 0;
		(*argv)++;
	}
	while (*argv) //check if end is the next cmd or the last arg
	{
		printf("%s", (*argv));
		(*argv)++;
		if (*argv)
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (0);
}

// int main(int ac, char **ag, char **envp)
// {
//    (void)ac;
//    (void)ag;
//    while (1)
//    {
// 		char *input = readline("Minishell> ");
// 		t_token *token = tokenizer(input);
// 		t_files *env = cp_env(envp);
// 		parsing(&token, env);
// 		// print_token(token);
// 		t_token *end = token;
// 		while (end->next)
// 			end = end->next;
// 		cmd_echo(token, end);
// 	}
//     return 0;
// }
