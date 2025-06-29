#include "minishell.h"

// function to check if $? at the beginning of a token
// if not, concat the string and the $? , make it type EXIT_CODE
void    check_prev_exitcode(t_token **lst, t_token **cur_token)
{
        t_token *curr;
        char *pre_value;
        char *tail_value;

        pre_value = NULL;
        tail_value = NULL;
        if (((*cur_token)->has_leading_space != 0 && !ft_strncmp((*cur_token)->value, "$?", 2))
                        || *cur_token == *lst)
            return ;
        curr = *lst;
        while (curr->next != *cur_token)
            curr = curr->next;
        pre_value = ft_strdup(curr->value);
        if (!pre_value)
            return ;
        tail_value = ft_strdup((*cur_token)->value); //$?$USER
        lst_rm_token(lst, cur_token);
        free(curr->value);
        curr->value = ft_strjoin(pre_value, tail_value);
        curr->type = EXIT_CODE;
        if (!curr->value)
            return ;
}

int if_exit_code(t_token **cur_token)
{
    char *var;

    var = (*cur_token)->value + 1; //?
    if_braces(&var);
    if (!ft_strchr(var, '?'))
        return (0);
    if (var[0] == '?')
    {
        (*cur_token)->type = EXIT_CODE;
        // update_token(cur_token, (*cur_token)->value, (*cur_token)->value + 2, WORD);
        //check_prev_exitcode(lst, cur_token);
        return (1);
    }
    return (0);
}