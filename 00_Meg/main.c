#include "minishell.h"

// funtion to print the str of the type -> remove later 
char *print_out_type(t_token_type type)
{
    switch (type)
    {
        case WORD: return "WORD";
        case SINGLE_QUOTE: return "SINGLE_QUOTE";
        case DOUBLE_QUOTE: return "DOUBLE_QUOTE";
        case COMMAND: return "COMMAND";
        case ARGUMENT: return "ARGUMENT";
        case PIPE: return "PIPE";
        case REDIRECTION: return "REDIRECTION";
        case LOGICAL_OR: return "LOGICAL_OR";
        case LOGICAL_AND: return "LOGICAL_AND";
        case ENV_VARIABLE: return "ENV_VARIABLE";
		case PID: return "PID";
        default: return "UNKNOWN";
    }
}

// function to print tokens in the lst -> remove later
void print_token(t_token *token)
{
	if (!token)
	{	printf("mal\n");
		return ;
	}
	while (token)
	{
		printf("\nvalue: %s, type: %s\n", token->value, print_out_type(token->type));
		token = token->next;
	}
}

int main(void)
{
	char *input;
	t_token *token;

	// while (1)
	// {
		input = readline("Minishell> "); //echo -n "this is test" $USER | grep "test" >> outfile  
		if (!ft_strncmp(input, "exit", 4))
			// break;
			return 1;
		token = tokenizer(input);
		print_token(token);
		//parsear()
		//execution()
	// }
	return 0;
}