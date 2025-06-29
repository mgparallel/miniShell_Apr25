#include "minishell.h"

// funtion used to check the end of env_var
// it stops where ch != letter, number or underscore or curly brackets
int if_alnum_underscore_braces(int arg)
{
    if (!ft_isalnum(arg))
        return (arg == '_' || arg == '{' || arg == '}');
    else
        return (1);
}

void	if_cmd(t_token **lst)
{
		t_token *cur_token;
		t_token *prev;
		int cmd_flag;

		cur_token = *lst;
		cmd_flag = 0;
		prev = NULL;
		while (cur_token)
		{
			if (prev && prev->type == REDIRECT)
				cur_token->type = RE_TARGET;
			else
			{
				if (cur_token->type == PIPE || cur_token->type == AND || cur_token->type == OR)
					cmd_flag = 0;
				else if (cur_token->type != REDIRECT && cur_token->type != AND && cur_token->type != OR)
				{
					if (!cmd_flag)
					{
						cur_token->type = CMD;
						cmd_flag = 1;
					}
					else
                    {
                        if (cur_token->type != EXIT_CODE)
						    cur_token->type = ARG;
                    }
				}
			}
			prev = cur_token;
			cur_token = cur_token->next;
		}
}

void join_exitcode_tokens(t_token **lst)
{
    t_token *head;
    char *new_value;
    t_token *next_node;

    new_value = NULL;
    head = *lst;
    next_node = head;
    while (head)
    {
        if (head->next)
        {
            next_node = head->next;
            if (head->next->type == EXIT_CODE && !head->next->has_leading_space)
            {
                new_value = ft_strjoin(head->value, head->next->value);
                if (!new_value)
                    return ;
                free(head->value);
                head->value = new_value;
                free(head->next);
                free(head->next->value);
                head->next = next_node;
            }
        }
        head = head->next;
    }
}

// main function of PARSING to refine the tokens
void parsing(t_token **lst, t_files *env)
{
    t_token *head;

    if (!*lst || !lst)
        return ;
    head = *lst;
    while (head)
    {
        if (head->type == WORD)
        {
            parse_type_word(&head);
            var_found(&head);
        }
        if (head->type == SINGLE_QUOTE || head->type == DOUBLE_QUOTE)
			parse_type_quote(&head);
        if (head->type == ENV_VAR)
        {
                if (parse_type_var(lst, &head, env))
                    continue ;
        }
        if (head->type == ARG)
            parse_type_arg(lst, &head);
        if (head->type == WILDCARD)
            expand_wildcard(lst, &head);
        head = head->next;
    }
    if_cmd(lst);
    join_exitcode_tokens(lst);
}