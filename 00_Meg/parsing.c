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

void if_cmd_util(t_token **lst)
{
	t_token *cur_token;
	int	cmd_flag;

	cur_token = *lst;
	cmd_flag = 0;
	while (cur_token)
	{
		if (cur_token->type == CMD && !cmd_flag)
			cmd_flag = 1;
		else if (cur_token->type == CMD)
			cur_token->type = ARG;
		else if (cur_token->type == PIPE)
			cmd_flag = 0;
		cur_token = cur_token->next;
	}
}

void if_cmd(t_token **lst)
{
    t_token *cur_token;
    t_token *prev;

    cur_token = *lst; // the begining of the list, used to parse until the one before cur_token
    if (cur_token->type != PIPE && cur_token->type != REDIRECT)
        cur_token->type = CMD;
    prev = cur_token;
    cur_token = cur_token->next;
    while (cur_token)
    {
        if (cur_token->type == WORD || cur_token->type == ARG)
        {
            if (prev->type == PIPE || prev->type == AND || prev->type == OR || prev->type == RE_TARGET)
                cur_token->type = CMD;
            else if (prev->type == REDIRECT)
                cur_token->type = RE_TARGET;
            else
                cur_token->type = ARG;
        }
        prev = cur_token;
        cur_token = cur_token->next;
    }
	if_cmd_util(lst);
}

void update_token(t_token **lst, char *str, char *quote_pos, t_token_type type)
{
    t_token *current_token;
    t_token *quote_token;
    char *first_value;
    char *original;

    current_token = *lst;
    original = current_token->value;
    quote_token = malloc(sizeof(t_token));
    if (!quote_token)
        return ;
    first_value = ft_strcpy(str, quote_pos);
    if (!first_value)
    {
        free(quote_token);
        return ;
    }
    quote_token->value = ft_strdup(quote_pos);
    if (!quote_token->value)
    {
        free(quote_token);
        free(first_value);
        return ;
    }
    current_token->value = first_value;
    quote_token->type = type;
    quote_token->has_leading_space = 0;
    quote_token->next = current_token->next;
    current_token->next = quote_token;
    free(original);
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
                parse_type_quote(lst, &head, env);
        if (head->type == ENV_VAR)
                parse_type_var(lst, &head, env);
        if (head->type == ARG)
            parse_type_arg(lst, &head);
        if (head->type == WILDCARD)
            expand_wildcard(lst, &head);
        head = head->next;
    }
    if_cmd(lst);
}