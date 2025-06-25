#include "minishell.h"

int    lst_rm_token(t_token **lst, t_token **cur_token)
{
    t_token *prev;
    t_token *temp;
    int if_space;

    if_space = (*cur_token)->has_leading_space;
    prev = *lst;
    if (*lst == *cur_token)
    {
        temp = *lst;
        *lst = temp->next;
        free(temp->value);
        free(temp);
        return (if_space);
    }
    temp = (*cur_token)->next;
    while (prev->next != *cur_token)
        prev = prev->next;
    prev->next = temp;
    free((*cur_token)->value);
    free(*cur_token);
    *cur_token = temp;
    return (if_space);
}