#include "minishell.h"

int main(void)
{
	char *input;

	while (1)
	{
		input = readline("Minishell> "); //echo  -n "this is test" | grep "test" > outfile
		if (!ft_strncmp(input, "exit", 4))
			break;
		tokenizer(input);

		//parsear()
		//ejecucion()
	}
	return 0;
}