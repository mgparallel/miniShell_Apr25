#include "minishell.h"

void free_lst(t_files **lst);

// funtion to print the str of the type -> remove later 
char *print_out_type(t_token_type type)
{
    switch (type)
    {
        case WORD: return "WORD";  //0
        case SINGLE_QUOTE: return "SINGLE_QUOTE"; //1
        case DOUBLE_QUOTE: return "DOUBLE_QUOTE"; //2
        case CMD: return "CMD"; //3
        case ARG: return "ARG"; //4
        case PIPE: return "PIPE"; //6
        case REDIRECT: return "REDIRECT"; //7
		case RE_TARGET: return "RE_TARGET"; //8
        case OR: return "OR"; //9
        case AND: return "AND"; //10
		case WILDCARD: return "WILDCARD"; //11
        case ENV_VAR: return "ENV_VAR"; //12
		case PID: return "PID"; //13
		case EXIT_CODE: return "EXIT_CODE"; //14
        default: return "UNKNOWN"; //15
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
		if (token->type == WILDCARD)
		{
			if (token->lst)
        	{
				while ((token->lst->value)[0] == '.')
					token->lst = token->lst->next;
				printf("WILDCARD VALUE: %s ", token->lst->value);
				while (token->lst)
				{
					printf("%s ", token->lst->value);
					token->lst = token->lst->next;
				}
			}
			else
				printf("WILDCARD->Literal value: %s\n", token->value);
		}
		else
			printf("\nVALUE: %s, TYPE: %s, SPACE? %d \n", token->value, print_out_type(token->type), token->has_leading_space);
		token = token->next;
	}
	printf("\n");
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

int main(int argc, char **argv, char **envp)
{
	char *input;
	t_token *token;
	t_files *env;
	char exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	while (1)
	{
		input = readline("Minishell> "); //echo -n "this is test" $USER | grep "test" >> outfile  
		if (!input)
		{
			printf("No input");
			return (1);
		}
		add_history(input);
		env = cp_env(envp);
		token = tokenizer(input);
		parsing(&token, env);
		print_token(token);
		clear_token(&token);
		// exit_status = execution(token, env);
		free(input);
	}
	rl_clear_history();
	return (0);
}