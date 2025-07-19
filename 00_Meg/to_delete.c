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
}

const char *redir_type_to_str(t_redir_type type)
{
	switch (type)
	{
		case REDIR_INPUT:      return "<";
		case REDIR_OUTPUT:     return ">";
		case REDIR_APPEND:  return ">>";
		case REDIR_HEREDOC: return "<<";
		default:            return "UNKNOWN";
	}
}

const char *connector_to_str(t_token_type type)
{
	switch (type)
	{
		case PIPE:       return "|";
		case AND:return "&&";
		case OR: return "||";
		default:         return "END";
	}
}

void print_cmd_list(t_cmd *cmd)
{
	int i, cmd_num = 1;

	while (cmd)
	{
		printf("Comando %d:\n", cmd_num++);

		// Argumentos
		printf("  argc: %d\n", cmd->argc);
		printf("  argv: ");
		for (i = 0; i < cmd->argc; i++)
			printf("[%s] ", cmd->argv[i]);
		printf("\n");
		
		// Redirecciones
		if (cmd->redir_list)
		{
			t_redir *r = cmd->redir_list;
			printf("  Redirecciones:\n");
			while (r)
			{
				printf("    tipo: %s, archivo: %s\n", redir_type_to_str(r->type), r->filename);
				r = r->next;
			}
		}
		else
		{
			printf("  Redirecciones: ninguna\n");
		}

		// Conector
		printf("  Conector: %s\n", connector_to_str(cmd->connector));
		printf("\n");

		cmd = cmd->next;
	}
}