#include "minishell.h"

void    lst_rm_token(t_token **lst, t_token **cur_token)
{
    t_token *prev;
    t_token *temp;

    prev = *lst;
    if (*lst == *cur_token)
    {
        temp = *lst;
        *lst = temp->next;
        free(temp->value);
        free(temp);
        return ;
    }
    while (prev->next != *cur_token)
        prev = prev->next;
    prev->next = (*cur_token)->next;
    free((*cur_token)->value);
    free(*cur_token);
}