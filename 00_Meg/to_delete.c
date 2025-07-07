#include "minishell.h"

char *print_out_type(t_token_type type)
{
    switch (type)
    {
        case WORD: return "WORD";  //0
        case SINGLE_QUOTE: return "SINGLE_QUOTE"; //1
        case DOUBLE_QUOTE: return "DOUBLE_QUOTE"; //2
        case CMD: return "CMD"; //3
        case ARG: return "ARG"; //4
        case PIPE: return "PIPE"; //5
        case REDIRECT: return "REDIRECT"; //6
		case RE_TARGET: return "RE_TARGET"; //7
        case OR: return "OR"; //8
        case AND: return "AND"; //9
		case WILDCARD: return "WILDCARD"; //10
        case ENV_VAR: return "ENV_VAR"; //11
		case PID: return "PID"; //12
		case EXIT_CODE: return "EXIT_CODE"; //13
        default: return "UNKNOWN"; //14
    }
}

void print_token(t_token *token)
{
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
			printf("\nVALUE: %s, TYPE: %s, SPACE? %d, IN_QUOTE? %d\n", token->value, print_out_type(token->type), token->has_leading_space, token->in_quote);
		token = token->next;
	}
	printf("\n");
}
