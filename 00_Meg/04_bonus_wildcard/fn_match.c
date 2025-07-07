#include "../minishell.h"

void free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    arr = NULL;
}

void fn_match_util(char **arr, t_files **fn_lst, t_files **result)
{
    char *trimmed;
    char **temp;
    int flag; //mark valid filenames with flag = 1

    temp = NULL;
    trimmed = NULL;
    flag = 0;
    while (*fn_lst) //iterate filename by filename calling ->next
    {
        if_end_to_match(arr, &flag);
        temp = arr;
        if (temp[0][0] != '*') //when * NOT at the begining e.g. mini*.h, ft_*
        {
            if (ft_strncmp((*fn_lst)->value, *temp, ft_strlen(*temp)))
            {
                *fn_lst = (*fn_lst)->next;
                continue ;
            }
        }
        else
            temp++;
        trimmed = (*fn_lst)->value;
        while (*++temp)
        {
            trimmed = strmatch(trimmed, *(temp - 1));
            if (!trimmed)
            {
                if (arr[0][0] == '*' && !temp++)
                    flag = 1;
                break ;
            }
            else if (*trimmed == '\0')
            {
                if (!temp++)
                    flag = 1;
            }
        }
        if (trimmed && trimmed[0] != '\0')
        {
            if (flag != -1)
                flag = 1;
            else
            {
                trimmed = trimmed + ft_strlen(trimmed) - ft_strlen(*(temp - 1));
                if (!ft_strcmp(trimmed, *(temp - 1)))
                    flag = 1;
            }
        }
        update_result((*fn_lst)->value, result, &flag);
        *fn_lst = (*fn_lst)->next;
    }
}

void fn_match(t_files *fn_lst, char *value, t_files **result)
{
    char **arr; //to store str after splitting
    char **updated_arr;
    
    updated_arr = NULL;
    arr = ft_split(value, '*'); //*
    if (!arr) 
        return ; //error with split function
    if (!*arr || *value == '*') //when the pointer is '\0' / * at the beginning of token value
        updated_arr = prepend_arr(arr, value, "*");
    else if (value[ft_strlen(value) - 1] == '*') //find * at the end of the token value
        updated_arr = append_arr(arr, "*");
    else
        updated_arr = arr;
    if (!updated_arr)
    {
        free(arr);
        return ;
    }
    fn_match_util(updated_arr, &fn_lst, result);
}