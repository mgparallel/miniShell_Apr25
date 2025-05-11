#include "minishell.h"

// funtion to check if the the token_type can be further refine as
// command, argument, redirection or re_target
void if_cmd(t_token **lst, t_token **cur_token)
{
    t_token *head;

    head = *lst; // the begining of the list, used to parse until the one before cur_token
    if (head == *cur_token)
    {
        (*cur_token)->type = COMMAND;
        return ;
    }
    while (head->next != *cur_token)
        head = head->next;
    if (head->type == PIPE || head->type == LOGICAL_AND || head->type == LOGICAL_OR || head->type == RE_TARGET)
        (*cur_token)->type = COMMAND;
    else if (head->type == REDIRECTION)
        (*cur_token)->type = RE_TARGET;
    else if ((*cur_token)->type != ENV_VAR)
        (*cur_token)->type = ARGUMENT;
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

// function to check if env_var is $?
// so it should update the type to EXIT_CODE and create new token if applicable
int if_exit_code(t_token **cur_token)
{
    if (!ft_strncmp((*cur_token)->value, "$?", 2))
    {
        (*cur_token)->type = EXIT_CODE;
        if (ft_strlen((*cur_token)->value) > 2)
            update_token(cur_token, (*cur_token)->value, (*cur_token)->value + 2, ARGUMENT);
        return (1);
    }
    return (0);
}

void if_braces(char **var)
{
    char *pos;

    pos = NULL;
    if (*var[0] == '{')
    {
        pos = ft_strchr(*var, '}');
        if (!pos)
            return ;
        else if (*(pos + 1) == '\0')
        {
            *var = ft_strcpy(*var + 1, pos);
            printf("var: %s\n", *var);
            if (!*var)
                return ;
        }
    }
}

// function to check if ENV_VAR are valid
void parse_type_var(t_token **cur_token)
{
    char *var;
    char *expand_value;
    char *pos; //pointer where var ends as finding NOT-{0-9a-zA-Z_}

    if (if_exit_code(cur_token))
        return ;
    pos = (*cur_token)->value + 1;
    while (if_alnum_underscore_braces(*pos))
    {
        if (*pos == '}')
            break ;
        pos++;
    }
    if (*pos != '\0' || *pos == '}') //we seperate into 2 tokens: VAR and ARGUMENT
    {
        update_token(cur_token, (*cur_token)->value, pos, ARGUMENT);
        var = (*cur_token)->value + 1;
    }
    else
        var = ft_strdup((*cur_token)->value + 1);
    if (!var)
        return ;
    if_braces(&var);
    expand_value = getenv(var);
    if (!expand_value)
        (*cur_token)->value = "(null)";
    else
        (*cur_token)->value = expand_value;
    (*cur_token)->type = ARGUMENT;
}

// funtion to expand the variable in case is valid
void expand_var(t_token **cur_token, char *pos)
{
    char *original;
    char *end_of_str;
    char *first_part; //string before $
    char *var; //str to pass to getenv()

    original = (*cur_token)->value;
    first_part = ft_strcpy(original + 1, pos);
    if (!first_part)
        return ;
    end_of_str = ft_strrchr(original, '\0');
    var = ft_strcpy(pos + 1, end_of_str - 1);
    if (!var)
        return (free(first_part));
    if (!getenv(var))
    {
        printf("Varilable not valid");
        return ;
    }
    free(original);
    original = ft_strjoin(first_part, getenv(var));
    (*cur_token)->value = original;
    (*cur_token)->type = ARGUMENT;
}

// funtion to remove quotes outside of literal value
void remove_outer_quote(t_token **lst, t_token **cur_token)
{
    char *original;
    char *new_value;
    char *end;

    original = (*cur_token)->value;
    end = ft_strrchr(original, *original);
    new_value = ft_strcpy(original + 1, end);
    if (!new_value)
        return ;
    (*cur_token)->value = new_value;
    if_cmd(lst, cur_token);
    free(original);
}

// funtion to check if single quote/double quote contains $
// remove outer quotes and deceide if expand
void parse_type_quote(t_token **lst, t_token **cur_token)
{
    char *dollar_pos;

    dollar_pos = ft_strchr((*cur_token)->value, '$');
    if (dollar_pos && (*cur_token)->type == DOUBLE_QUOTE)
        expand_var(cur_token, dollar_pos);
    else
        remove_outer_quote(lst, cur_token);
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
        if (head->type == WORD)
            parse_type_word(lst, &head);
        if (head->type == SINGLE_QUOTE || head->type == DOUBLE_QUOTE)
            parse_type_quote(lst, &head);
        if (head->type == ENV_VAR)
            parse_type_var(&head);
        // if (head->type == ARGUMENT)
        //     parse_type_arg();
    //     else if (head->type == 9)
    //         parse_variable();
        head = head->next;
    }

}