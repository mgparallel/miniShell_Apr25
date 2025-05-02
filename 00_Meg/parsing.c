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


// funtion to expand the variable
void expand_var(t_token **lst, char *pos)
{
    char *original;
    char *end_of_str;
    char *start; //string before $
    char *var; //str to pass to getenv()


    original = (*lst)->value;
    start = ft_strcpy(original + 1, pos);
    if (!start)
        return ;
    end_of_str = original;
    while (*(end_of_str + 1))
        end_of_str++; // where the quote is
    var = ft_strcpy(pos + 1, end_of_str);
    if (!var)
        return (free(start));
    if (!getenv(var))
    {
        printf("Varilable not valid");
        return ;
    }
    free(original);
    original = ft_strjoin(start, getenv(var));
    (*lst)->value = original;
    //if_cmd(lst, lst);
}

// funtion to remove quotes outside of literal value
void remove_outer_quote(t_token **lst)
{
    t_token *cur_token;
    char *original;
    char *new_value;

    cur_token = *lst;
    original = cur_token->value;
    new_value = malloc(ft_strlen(original - 1));
    if (!new_value)
        return ;
    ft_strlcpy(new_value, original + 1, ft_strlen(original) - 1);
    if (!new_value)
        return ;
    cur_token->value = new_value;
    //if_cmd(lst, &cur_token);
    free(original);
}

// funtion to check if single quote/double quote contains $
// remove outer quotes and deceide if expand
void parse_type_quote(t_token **lst)
{
    char *dollar_pos;

    dollar_pos = ft_strchr((*lst)->value, '$');
    if (dollar_pos && (*lst)->type == DOUBLE_QUOTE)
        expand_var(lst, dollar_pos);
    remove_outer_quote(lst);
}

// funtion to parse ARGUMENT to see if * find


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
            parse_type_word(&head);
            if (head == *lst)
                head->type = COMMAND;
            else
                if_cmd(lst, &head);
        }
        if (head->type == SINGLE_QUOTE || head->type == DOUBLE_QUOTE)
            parse_type_quote(&head);
        // if (head->type == ARGUMENT)
        //     parse_type_arg();
    //     else if (head->type == 9)
    //         parse_variable();
        head = head->next;
    }

}