#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>

void fn_match(t_files_indir *fn_lst, char *value, t_files_indir **result);
char **append_arr(char **arr, char *str);
char **prepend_arr(char **arr, char *str);
void free_arr(char **arr);

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
            break ;
    }
    closedir(dir);
}

// funtion to find if small can be found in big
// if so, return the pointer right after smalls are found
char *strmatch(const char *big, const char *little)
{
    int i;

    i = 0;
    if (*little == '\0')
        return ((char *)big);
    while (*big)
    {
        i = 0;
        while (big[i] && little[i] && big[i] == little[i])
        {
            i++;
            if (little[i] == '\0')
            {
                while (i--)
                    big++;
                return ((char *)big);
            }
        }
        big++;
    }
    return (NULL);
}

void update_result(char *value, t_files_indir **result, int *flag)
{
    t_files_indir *new;

    new = malloc(sizeof(t_files_indir));
    if (!new)
        return ;
    if (*flag == 0)
        return (free(new));
    new->value = ft_strdup(value);
    if (!new->value)
        return (free(new));
    new->next = NULL;
    *flag = 0;
    indir_lst_addback(result, new);
}

void fn_match_util(char **arr, t_files_indir **fn_lst, t_files_indir **result)
{
    char *trimmed;
    char **temp;
    int flag; //mark valid filenames with flag = 1

    temp = NULL;
    trimmed = NULL;
    flag = 0;
    while (*fn_lst) //iterate filename by filename calling ->next
    {
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
        while (*temp)
        {
            trimmed = strmatch(trimmed, *temp);
            if (!trimmed)
            {
                if (temp[0][0] == '*' || !temp[1])
                    flag = 1;
                break ;
            }
            if (*trimmed == '\0')
            {
                if (!temp[1] || temp[1][0] == '*')
                    flag = 1;
            }
            temp++;
        }
        update_result((*fn_lst)->value, result, &flag);
        *fn_lst = (*fn_lst)->next;
    }
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
        return (NULL);
    fn_match(fn_lst, value, &result);
    return (result);
}

// int main(void)
// {
//     char *value = "mini*";

//     t_files_indir *result = expand_wildcard(value);
//     if (!result)
//     {
//         printf("no result\n");
//         return (1);
//     }
//     while ((result->value)[0] == '.')
//         result = result->next;
//     printf("cmd: echo %s\nresult found: ", value);
//     while (result)
//     {
//         printf("%s ", result->value);
//         result = result->next;
//     }
//     return 0;
// }