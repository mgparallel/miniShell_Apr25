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
		case EXIT_CODE: return "EXIT_CODE"; //5
        case PIPE: return "PIPE"; //6
        case REDIRECTION: return "REDIRECTION"; //7
		case RE_TARGET: return "RE_TARGET"; //8
        case LOGICAL_OR: return "LOGICAL_OR"; //9
        case LOGICAL_AND: return "LOGICAL_AND"; //10
		case WILDCARD: return "WILDCARD"; //11
        case ENV_VARIABLE: return "ENV_VARIABLE"; //12
		case PID: return "PID"; //13
        default: return "UNKNOWN"; //14
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

void clear_token(t_token **token)
{
	while (*token)
	{
		free(*token);
		*token = (*token)->next;
	}
	*token = NULL;
}

void clean_exit(t_token **token)
{
	while (*token)
	{
		free((*token)->value);
		free(*token);
		*token = (*token)->next;
	}
	//free(token);
}

int main(void)
{
	char *input;
	t_token *token;

	while (1)
	{
		input = readline("Minishell> "); //echo -n "this is test" $USER | grep "test" >> outfile  
		if (!input)
		{
			printf("No input");
			return (1);
		}
		add_history(input);
		//copy_env()
		if (!ft_strncmp(input, "exit", 4))
		{
			clean_exit(&token);
			break;
		}
		token = tokenizer(input);
		parsing(&token);
		print_token(token);
		clear_token(&token);
		// execution()
	}
	rl_clear_history();
	return 0;
}