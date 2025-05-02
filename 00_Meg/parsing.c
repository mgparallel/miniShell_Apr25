#include "minishell.h"

void if_cmd(t_token **lst, t_token **current_token)
{
    t_token *head;
    t_token *cur_token;

    head = *lst;
    cur_token = *current_token;
    while (head->next != cur_token)
        head = head->next;
    if (head->type == PIPE || head->type == LOGICAL_AND || head->type == LOGICAL_OR || head->type == RE_TARGET)
        cur_token->type = COMMAND;
    else if (head->type == REDIRECTION)
        cur_token->type = RE_TARGET;
    else
        cur_token->type = ARGUMENT;
}

void update_token(t_token **lst, char *str, char *quote_pos, t_token_type type)
{
    t_token *current_token;
    t_token *quote_token;
    char *cmd_value;
    char *original;

    current_token = *lst;
    original = current_token->value;
    quote_token = malloc(sizeof(t_token));
    if (!quote_token)
        return ;
    cmd_value = ft_strcpy(str, quote_pos);
    if (!cmd_value)
        return ;
    quote_token->value = ft_strdup(quote_pos);
    if (!quote_token->value)
        return ;
    current_token->value = cmd_value;
    quote_token->value = ft_strdup(quote_pos);
    if (!quote_token->value)
        return (free(cmd_value));
    quote_token->type = type;
    quote_token->has_leading_space = 0;
    quote_token->next = current_token->next;
    current_token->next = quote_token;
    free(original);
}

// funton to parse the token with type="WORD"
// output->add new token if quotes found
// send to fucntion update)_quote() or return error if quote not closed
void parse_type_word(t_token **lst)
{
    t_token *token;
    char *str;
    char *s_quote_pos;
    char *d_quote_pos;

    token = *lst;
    str = token->value;
    s_quote_pos = ft_strchr(str, '\'');
    d_quote_pos = ft_strchr(str, '"');
    if (!s_quote_pos && !d_quote_pos)
        return ;
    if (s_quote_pos && (!d_quote_pos || s_quote_pos < d_quote_pos))
    {
        if (*(ft_strrchr(str, '\'') + 1) != '\0')
        {
            printf("Quote not closed\n");
            return ; //should have a error exit
        }
        update_token(lst, str, s_quote_pos, SINGLE_QUOTE);
    }
    else
    {
        if (*(ft_strrchr(str, '"') + 1) != '\0')
        {
            printf("Quote not closed\n");
            return ; //should have a error exit
        }   
        update_token(lst, str, d_quote_pos, DOUBLE_QUOTE);
    }
}

// function to check if ENV_VARIABLE are valid


// funtion to check if single quote/double quote contains $
// remove quotes and deceide if expand



// main function of parsing to refine the tokens

void parsing(t_token **lst)
{
    t_token *head;

    if (!*lst || !lst)
        return ;
    head = *lst;
    while (head)
    {
        if (head->type == WORD)
        {
            // printf("check token: value=%s, type=%i\n", head->value, head->type);
            parse_type_word(&head);
            if (head == *lst)
                head->type = COMMAND;
            else
                if_cmd(lst, &head);
        }
    //     else if (head->type == 1)
    //         parse_single_quote();
    //     else if (head->type == 2)
    //         parse_double_quote();
    //     else if (head->type == 9)
    //         parse_variable();
        head = head->next;
    }

}