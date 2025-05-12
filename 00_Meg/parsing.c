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

// funtion to check if the the token_type can be further refine as
// command, argument, redirection or re_target
void if_cmd(t_token **lst, t_token **cur_token)
{
    t_token *head;

    head = *lst; // the begining of the list, used to parse until the one before cur_token
    if (head == *cur_token)
    {
        (*cur_token)->type = CMD;
        return ;
    }
    while (head->next != *cur_token)
        head = head->next;
    if (head->type == PIPE || head->type == AND || head->type == OR || head->type == RE_TARGET)
        (*cur_token)->type = CMD;
    else if (head->type == REDIRECT)
        (*cur_token)->type = RE_TARGET;
    else if ((*cur_token)->type != ENV_VAR)
        (*cur_token)->type = ARG;
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
void parsing(t_token **lst)
{
    t_token *head;

    if (!*lst || !lst)
        return ;
    head = *lst;
    while (head)
    {
        var_found(&head);
        if (head->type == ENV_VAR)
            parse_type_var(&head);
        if (head->type == WORD)
            parse_type_word(lst, &head);
        if (head->type == SINGLE_QUOTE || head->type == DOUBLE_QUOTE)
            parse_type_quote(lst, &head);
        if (head->type == ARG)
            parse_type_arg(lst, &head);
        head = head->next;
    }

}