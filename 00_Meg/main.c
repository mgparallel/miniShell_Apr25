#include "minishell.h"

// funtion to print the str of the type -> remove later 
char *print_out_type(t_token_type type)
{
    switch (type)
    {
        case WORD: return "WORD";  //0
        case SINGLE_QUOTE: return "SINGLE_QUOTE"; //1
        case DOUBLE_QUOTE: return "DOUBLE_QUOTE"; //2
        case COMMAND: return "COMMAND"; //3
        case ARGUMENT: return "ARGUMENT"; //4
        case PIPE: return "PIPE"; //5
        case REDIRECTION: return "REDIRECTION"; //6
		case RE_TARGET: return "RE_TARGET"; //7
        case LOGICAL_OR: return "LOGICAL_OR"; //8
        case LOGICAL_AND: return "LOGICAL_AND"; //9
        case ENV_VARIABLE: return "ENV_VARIABLE"; //10
		case PID: return "PID"; //11
        default: return "UNKNOWN"; //12
    }
}

// function to print tokens in the lst -> remove later
void print_token(t_token *token)
{
	if (!token)
	{	printf("No token\n");
		return ;
	}
	while (token)
	{
		// printf("\nVALUE: %s, TYPE: %d, SPACE? %d \n", token->value, token->type, token->has_leading_space);
		printf("\nVALUE: %s, TYPE: %s, SPACE? %d \n", token->value, print_out_type(token->type), token->has_leading_space);
		token = token->next;
	}
}

int main(void)
{
	char *input;
	t_token *token;

	while (1)
	{
		input = readline("Minishell> "); //echo -n "this is test" $USER | grep "test" >> outfile  
		if (!ft_strncmp(input, "exit", 4))
			break;
		token = tokenizer(input);
		parsing(&token);
		print_token(token);
		// parsear()
		// execution()
	}
	return 0;
}