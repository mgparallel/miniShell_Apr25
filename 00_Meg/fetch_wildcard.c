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

void	indir_lst_addback(t_files_indir **lst, t_files_indir *new)
{
	t_files_indir	*ref;

	if (lst == NULL || new == NULL)
		return ;
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

// funtion to check if wildcard is valid (can find corespondence)
// or is a literal argument
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
            free_fn(fn_lst);
            break ;
        }
    }
    closedir(dir); 
}

//function to check if the current token is type WILDCARD
bool if_wildcard(t_token **cur_token)
{
    char *str;
    char *pos;
    t_files_indir *fn_lst;

    str = (*cur_token)->value;
    fn_lst = NULL;
    pos = ft_strchr(str, '*');
    if (!pos)
        return (false);
    (*cur_token)->type = WILDCARD;
    fetch_wildcard(&fn_lst); //maybe need to make a seperate function
    return (true);
    // t_files_indir *temp =  NULL;
    // *temp = *fn_lst;
    // while (temp)
    // {
    //     printf("fn: %s\n", temp->value);
    //     temp = temp->next;
    // }
}

void fn_match_util(char **arr, t_files_indir **fn_lst, t_files_indir **result, int flag)
{
    t_files_indir *new;

    while (*fn_lst)
    {
        while (*arr)
        {
            if (ft_strtrim(*arr, (*fn_lst)->value))
            {
                new->value = ft_strdup(*arr);
                if (!new->value)
                    return ;
                indir_lst_addback(result, new);
            }
            arr++;
        }
        *fn_lst = (*fn_lst)->next;
    }
} //need to test if this function works 

// need to implement where if *wildcard is not found matching
// it turns into a literal. 
void fn_match(t_files_indir *fn_lst, char *value, t_files_indir *fn_lst)
{
    t_files_indir *result;
    int flag; //to mark if the token start with '*' or not
    char **arr; //to store str after splitting
    
    result = NULL;
    flag = 0;
    if (*value == '*')
        flag = 1;
    arr = ft_split(value, '*');
    if (!*arr && flag == 1) //when only one '*' is found
    {
        free(arr);
        printf(fn_lst); // TO-DO print all the filenames
        return ;
    }
    fn_match_util(arr, value, &fn_lst, flag);
    free();
}