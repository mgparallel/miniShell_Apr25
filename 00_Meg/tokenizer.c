#include "minishell.h"

int main()
{
	char *input;
	while (1)
	{
		input = readline("Minishell> ");
		//printf("the input: %s", input);
		if (!ft_strncmp(input, "exit", 4))
			break;
		
		//tokenizar()
		//parsear()
		//ejecuccion()
	}
}