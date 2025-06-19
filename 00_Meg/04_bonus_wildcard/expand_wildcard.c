#include "../minishell.h"

// funtion to free the prev tokens until the failing
void free_fn(t_files **fn)
{
    t_files *temp;

    while (*fn)
    {
        temp = (*fn)->next;
        free(*fn);
        *fn = temp;
    }
}

void    indir_lst_addback(t_files **lst, t_files *new)
{
	t_files	*ref;

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

//funtion to update the fn_lst stucture by adding new nodes.
void create_fn_lst(struct dirent *dp, t_files **fn_lst)
{
    t_files *new_token;

    new_token = malloc(sizeof(t_files));
    if (!new_token)
        return ;
    new_token->value = ft_strdup(dp->d_name);
    if (!new_token->value)
        return ;
    new_token->next = NULL;
    indir_lst_addback(fn_lst, new_token);
}

// funtion to create the filename_list by opendir()
void fetch_wildcard(t_files **fn_lst)
{
    struct dirent *dp;
    DIR *dir;

    dir = opendir(".");
    if (!dir)
    {
        printf("error opening directory");
        return ; //error code needed
    }
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
char *strmatch(const char *big, const char *little) //main.o  h
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

void update_result(char *value, t_files **result, int *flag)
{
    t_files *new;

    new = malloc(sizeof(t_files));
    if (!new)
        return ;
    if (*flag == 0 || *flag == -1)
        return (free(new));
    new->value = ft_strdup(value);
    if (!new->value)
        return (free(new));
    new->next = NULL;
    *flag = 0;
    indir_lst_addback(result, new);
}

void    if_end_to_match(char **arr, int *flag)
{
    char **ref;
    char *prev;

    ref = arr;
    prev = NULL;
    while (*ref)
    {
        prev = *ref;
        ref++;
    }
    if (!ft_strchr(prev, '*'))
        *flag = -1; //flag = -1 when the end has to match leters 100%
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

//function to check if the refent token is type WILDCARD
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

void expand_wildcard(t_token **lst, t_token **cur_token)
{
    t_files *fn_lst;
    t_files *result;

    fn_lst = NULL;
    result = NULL;
    fetch_wildcard(&fn_lst);
    if (!fn_lst)
        return ;
    fn_match(fn_lst, (*cur_token)->value, &result);
    if (!result)
    {
        (*cur_token)->type = WORD;
        return ;
    }
	add_wildcard_token(lst, *cur_token, result);
}

// int main(void)
// {
//     char *value = "c*.c";
//     t_files *result = NULL;

//     result = expand_wildcard(value);
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

// int main(void)
// {
//     char *str = "**";
//     char ch = '*';
//     char **re;

//     // printf("input:%s\n", str);
//     re = ft_split(str, ch);
//     if (!*re)
//         printf("null res\n");
//     while (*re)
//     {
//         printf("re: %s\n", *re);
//         re++;
//     }
//     // printf("result: %s\n", ft_strtrim(str, ch));
//     return 0;
// }

// char *strmatch(const char *big, const char *little)
// {
//     int i;
//     int j;

//     i = 0;
//     if (*little == '\0')
//         return ((char *)big);
//     while (big[i])
//     {
//         j = 0;
//         while (big[i + j] != '\0' && big[i + j] == little[j])
//             j++;
//         if (little[j] == '\0')
//             return ((char *)&big[i + j]);
//         i++;
//     }
//     return (NULL);
// }

// char *strmatch(const char *big, const char *little)
// {
//     int i;

//     i = 0;
//     if (*little == '\0')
//         return ((char *)big);
//     while (*big)
//     {
//         i = 0;
//         while (big[i] && little[i] && big[i] == little[i])
//         {
//             i++;
//             if (little[i] == '\0')
//             {
//                 while (i--)
//                     big++;
//                 return ((char *)big);
//             }
//         }
//         big++;
//     }
//     return (NULL);
// }

// int main(void)
// {
//     char *big = "exit_error.c";
//     char *small = "t_";

//     // big = strmatch(big, small);
//     printf("re: %s\n", strmatch(big, small));
//     return 0;
// }


/*
big = minishell.h
small = *ni*el*
small = mi*shell* //yes
small = mi*shel*l*.h //x
small = mini*
small = ma*
*/