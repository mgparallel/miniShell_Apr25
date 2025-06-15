#include "minishell.h"

void update_token_util(t_token **current_token, t_token **quote_token, char *first_value, t_token_type type)
{
    (*current_token)->value = first_value;
    (*quote_token)->type = type;
    (*quote_token)->has_leading_space = 0;
    (*quote_token)->next = (*current_token)->next;
    (*current_token)->next = *quote_token;
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
        return (free(quote_token));
    quote_token->value = ft_strdup(quote_pos);
    if (!quote_token->value)
        return (free(quote_token), free(first_value));
    update_token_util(&current_token, &quote_token, first_value, type);
    free(original);
}