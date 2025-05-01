#include "minishell.h"

void update_token(t_token **lst, char *str)
{
    t_token *cur_token;
    t_token *new_token;

    cur_token = *lst;
    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL); //need to check if free()
    new_token->value = ft_strcpy(str, );
    if (cur_token->next == NULL)
        lstadd_back(lst, );
}

// funton to parse the token with type="WORD"
// further define if the token is COMMAND or ARGUMENT
void parse_type_word(t_token **lst)
{
    t_token *token;
    char *str;

    token = *lst;
    str = token->value;
    while (*str)
    {
        if (*str == '\'')
        {
            update_token()
        }
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
        if (head->type == 0) //type "WORD"
            parse_type_word(&head);
        else if (head->type == 1)
            parse_single_quote();
        else if (head->type == 2)
            parse_double_quote();
        else if (head->type == 9)
            parse_variable();
        head = head->next;
    }

}