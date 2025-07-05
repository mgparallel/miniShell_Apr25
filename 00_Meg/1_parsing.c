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

int merge_exitcode_tokens(t_token **cur_token, t_token **next_node)
{
        char *new_value;

        new_value = ft_strjoin((*cur_token)->value, (*cur_token)->next->value);
        if (!new_value)
            return (printf("Failed malloc\n"), -1);
        free((*cur_token)->value);
        (*cur_token)->value = new_value;
        free((*cur_token)->next);
        free((*cur_token)->next->value);
        (*cur_token)->next = *next_node;
		return (0);
}

int join_exitcode_tokens(t_token **lst, t_token **cur_token)
{
    t_token *prev;
    t_token *next;

	if ((*cur_token)->has_leading_space)
		return (0);
    prev = *lst;
    next = (*cur_token)->next;
    while (prev->next && prev->next != *cur_token)
		prev = prev->next;
	return (merge_exitcode_tokens(&prev, &next));
}

int parsing_util(t_token **cur_token, t_token **lst)
{
    if ((*cur_token)->type == ARG)
    {
		if (parse_type_arg(lst, cur_token) == -1)	
			return (-1);
	}
    if ((*cur_token)->type == WILDCARD)
    {
		if (expand_wildcard(lst, cur_token) == -1)
			return (-1);
	}
	if ((*cur_token)->type == EXIT_CODE)
    {
		if (join_exitcode_tokens(lst, cur_token) == -1)
				return (-1);
	}
	return (0);
}

// main function of PARSING to refine the tokens
int parsing(t_token **lst, t_files *env)
{
    t_token *head;
	int	flag;

    head = *lst;
    while (head)
    {
		flag = 0;
        if (head->type == WORD)
        {
            parse_type_word(&head);
            if (var_found(&head) == -1)
				return (-1);
        }
        if (head->type == SINGLE_QUOTE || head->type == DOUBLE_QUOTE)
		{
			flag = parse_type_quote(&head);
            if (flag == -1)
				return (-1);
			else if (flag == 1)
                continue ;
        }
        if (head->type == ENV_VAR)
        {
                flag = parse_type_var(lst, &head, env);
				if (flag == -1)
					return (-1);
				else if (flag == 1)
                	continue ;
        }
        parsing_util(&head, lst);
        head = head->next;
    }
    if_cmd(lst);
	return (0);
}