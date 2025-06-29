#include "minishell.h"
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
		free((*token)->value);
		free(*token);
		*token = (*token)->next;
	}
}

void    handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
	t_token *token;
	t_files *env;
	t_cmd	*cmds;
	char	*input;
	int		exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	env = cp_env(envp);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("Minishell> "); //echo -n "this is test" $USER | grep "test" >> outfile  
		if (!input)
		{
			printf("exit\n");
			exit_status = 0;
			break ;
		}
		add_history(input);
		token = tokenizer(input);
		free(input);
		parsing(&token, env);
		print_token(token);
		if (!token)
			continue ;
		if (is_connector(token->type))
		{
			ft_putstr_fd("syntax error near unexpected token '", 2);
			ft_putstr_fd(token->value, 2);
			ft_putstr_fd("'\n", 2);
			exit_status = 1;
			continue ;
		}
		cmds = build_cmds(token);
		clear_token(&token);
		exec_commands(&cmds, &env, &exit_status);
		free_cmd_list(cmds);
	}
	free_lst(&env);
	rl_clear_history();
	return (exit_status);
}
