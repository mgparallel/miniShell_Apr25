#include "../minishell.h"

char **prepend_arr(char **arr, char *value, char *str)
{
    char **new_arr;
    int len;
    int i;
    int flag;

    len = 0;
    i = 0;
    flag = 0;
    while (arr[len])
        len++;
    if (value[ft_strlen(value) - 1] == '*')
    {
        new_arr = (char **)malloc(sizeof(char *) * (len + 3));
        flag = 1;
    }
    else
        new_arr = (char **)malloc(sizeof(char *) * (len + 2));
    if (!new_arr)
        return (NULL);
    new_arr[i] = ft_strdup(str);
    if (!new_arr[i])
        return (free(new_arr), NULL);
    while (i < len)
    {
        new_arr[i + 1] = arr[i];
        i++;
    }
    if (flag == 1)
    {
        new_arr[i + 1] = ft_strdup(str);
        if (!new_arr[i + 1])
            return (free_arr(new_arr), NULL);
        i++;
    }
    new_arr[i + 1] = NULL;
    return (new_arr);
}

char **append_arr(char **arr, char *str)
{
    char **new_arr;
    int len;
    int i;

    len = 0;
    i = 0;
    while (arr[len])
        len++;
    new_arr = (char **)malloc(sizeof(char *) * (len + 2));
    if (!new_arr)
        return (NULL);
    while (i < len)
    {
        new_arr[i] = arr[i];
        i++;
    }
    new_arr[i] = ft_strdup(str);
    if (!new_arr[i])
        return (free_arr(new_arr), NULL);
    new_arr[i + 1] = NULL;
    return (new_arr);
}

void fn_match(t_files *fn_lst, char *value, t_files **result)
{
    char **arr;
    char **updated_arr;
    
    updated_arr = NULL;
    arr = ft_split(value, '*');
    if (!arr) 
        return ;
    if (!*arr || *value == '*')
        updated_arr = prepend_arr(arr, value, "*");
    else if (value[ft_strlen(value) - 1] == '*')
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