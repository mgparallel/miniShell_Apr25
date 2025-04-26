#include "minishell.h"

int main(void)
{
	char *input;
	t_token **token;

	while (1)
	{
		input = readline("Minishell> "); //echo -n "this is test" | grep "test" > outfile  
		if (!ft_strncmp(input, "exit", 4))
			break;
		token = tokenizer(input);

		//parsear()
		//ejecucion()
	}
	return 0;
}