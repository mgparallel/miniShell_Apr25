#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>

// funtion to free the prev tokens until the failing
void free_fn(t_files_indir **fn)
{
    t_files_indir *temp;

    while (*fn)
    {
        temp = (*fn)->next;
        free(*fn);
        *fn = temp;
    }
}

void    indir_lst_addback(t_files_indir **lst, t_files_indir *new)
{
	t_files_indir	*ref;

	// if (lst == NULL || new == NULL)
	// 	return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ref = *lst;
	while (ref && ref->next)
		ref = ref->next;
	ref->next = new;
}

//funtion to update the fn_lst stucture by adding new nodes.
void create_fn_lst(struct dirent *dp, t_files_indir **fn_lst)
{
    t_files_indir *new_token;

    new_token = malloc(sizeof(t_files_indir));
    if (!new_token)
        return ;
    new_token->value = ft_strdup(dp->d_name);
    if (!new_token->value)
        return ;
    new_token->next = NULL;
    indir_lst_addback(fn_lst, new_token);
}

// funtion to create the filename_list by opendir()
void fetch_wildcard(t_files_indir **fn_lst)
{
    struct dirent *dp;
    DIR *dir;

    dir = opendir(".");
    if (!dir)
        return ; //error code needed
    while (1)
    {
        dp = readdir(dir);
        if (dp)
            create_fn_lst(dp, fn_lst);
        else
        {
            //free_fn(fn_lst);
            break ;
        }
    }
    closedir(dir);
    //print fn_lst
    t_files_indir *temp = *fn_lst;
    while(temp)
    {
        printf("filename: %s\n", temp->value);
        temp = temp->next;
    }
}

// funtion to find if small can be found in big
// if so, return the pointer right after smalls are found
char *strmatch(const char *big, const char *little)
{
    int i;
    int j;

    i = 0;
    if (*little == '\0')
        return ((char *)big);
    while (big[i])
    {
        j = 0;
        while (big[i + j] != '\0' && big[i + j] == little[j])
            j++;
        if (little[j] == '\0')
            return ((char *)&big[i + j]);
        i++;
    }
    return (NULL);
}

void update_result(char *value, t_files_indir **result, int *flag)
{
    t_files_indir *new;

    new = malloc(sizeof(t_files_indir));
    if (!new)
        return ;
    if (flag == 0)
        return (free(new));
    new->value = ft_strdup(value);
    if (!new->value)
        return (free(new));
    flag = 0;
    indir_lst_addback(result, new);
}

void fn_match_util(char **arr, t_files_indir **fn_lst, t_files_indir **result)
{
    char *trimmed;
    char **temp;
    int flag; //mark valid filenames with flag = 1

    trimmed = NULL;
    flag = 0;
    while (*fn_lst) //iterate filename by filename calling ->next
    {
        trimmed = ft_strdup((*fn_lst)->value);
        if (!trimmed)
            return ;
        temp = arr;
        if (ft_strncmp(*temp, "*", 1)) //when * NOT at the begining e.g. mini*.h, ft_*
        {
            if (ft_strncmp(trimmed, *temp, ft_strlen(*temp)))
                continue ;
        }
        while (*temp)
        {
            trimmed = strmatch(trimmed, *temp);
            if (!trimmed)
            {
                if ((**temp == '*') && !(*temp + 1))
                    flag = 1;
                break ;
            }
            else if (*trimmed == '\0')
            {
                if (!(*temp + 1))
                    flag = 1;
                break ;
            }
            temp++;
        }
        if (trimmed)
            free(trimmed);
        update_result((*fn_lst)->value, result, &flag);
        *fn_lst = (*fn_lst)->next;
    }
}

char **prepend_arr(char **arr, char *str)
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
    new_arr[i] = ft_strdup(str);
    if (!new_arr[i])
        return (free(new_arr), NULL);
    while (i < len + 1)
    {
        printf("in, i = %d\n", i);
        new_arr[i + 1] = arr[i];
        i++;
    }
    free(arr);
    return (new_arr);
}

char **append_arr(char **arr, char *str) //probelm here still
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
        return (free(new_arr), NULL);
    free(arr);
    int p = 0;
    while(new_arr[p])
    {
        printf("arr: %s\n", new_arr[p]);
        p++;
    }
    return (new_arr);
}

//funtion to parse the fn_lst and token value
//update result if the wildcard token if valid
void fn_match(t_files_indir *fn_lst, char *value, t_files_indir **result)
{
    char **arr; //to store str after splitting
    char **updated_arr;
    
    updated_arr = NULL;
    arr = ft_split(value, '*');
    if (!arr) 
        return ; //error with split function
    // int i = 0;
    // while(arr[i])
    // {
    //     printf("arr: %s\n", arr[i]);
    //     i++;
    // }
    if (!*arr || *value == '*') //when the pointer is '\0' / * at the beginning of token value
    {
        updated_arr = prepend_arr(arr, "*");
        if (!updated_arr)
        {
            free(arr);
            return ;
        }
    }
    if (ft_strrchr(value, '*') && *(ft_strrchr(value, '*') + 1) == '\0') //find * at the end of the token value
    {
        if (arr)
            updated_arr = append_arr(arr, "*");
        else
            arr = append_arr(updated_arr, "*");
    }
    if (updated_arr)
        arr = updated_arr;
    fn_match_util(arr, &fn_lst, result);
    // free(arr);
}

//function to check if the current token is type WILDCARD
bool if_wildcard(t_token **cur_token)
{
    char *str;
    char *pos;

    str = (*cur_token)->value;
    pos = ft_strchr(str, '*');
    if (!pos)
        return (false);
    (*cur_token)->type = WILDCARD;
    return (true);
}

t_files_indir *expand_wildcard(char *value)
{
    t_files_indir *fn_lst;
    t_files_indir *result;

    fn_lst = NULL;
    result = NULL;
    fetch_wildcard(&fn_lst);
    if (!fn_lst)
    {   printf("no fn_lst\n");
        return (NULL);
    }
    fn_match(fn_lst, value, &result);
    return (result);
} //need to test the function

int main(void)
{
    char *value = "*ni*.h*";

    t_files_indir *result = expand_wildcard(value);
    if (!result)
    {
        printf("no result\n");
        return (1);
    }
    while (result)
    {
        printf("result value: %s\n", result->value);
        result =result->next;
    }
    return 0;
}