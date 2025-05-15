#include "minishell.h"

void    lst_rm_token(t_token **lst, t_token **cur_token)
{
    t_token *prev;

    prev = *lst;
    while (prev->next != *cur_token)
        prev = prev->next;
    prev->next = (*cur_token)->next;
    free((*cur_token)->value);
    free(*cur_token);
}