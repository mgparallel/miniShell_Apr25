#include "../minishell.h"
//take into account that when echo "" is print out a new line
//when there are other cmds, it ignores.
int	cmd_echo(char **argv)
{
	int	nl;
	int	i;

	nl = 1;
	i = 0;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		nl = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (0);
}

// int main(int argc, char **argv)
// {
//     // Simula: echo -n hola
//     char *args[] = {"-n", "hola", NULL};
//     cmd_echo(args);

//     printf("\n---\n");

//     // Simula: echo hola
//     char *args2[] = {"hola", NULL};
//     cmd_echo(args2);

//     return 0;
// }
