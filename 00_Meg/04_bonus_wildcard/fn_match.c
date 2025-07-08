#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	arr = NULL;
}

void	if_flag(int *flag, char *trimmed, char *ptr)
{
	if (*flag != -1)
		*flag = 1;
	else
	{
		trimmed = trimmed + ft_strlen(trimmed) - ft_strlen(ptr);
		if (!ft_strcmp(trimmed, ptr))
			*flag = 1;
	}
}

// char	*initail_match(char **temp, char **arr, t_files **fn_lst, int *flag)
// {
//     if_end_to_match(arr, flag);
// 	temp = arr;
// 	if (temp[0][0] != '*' && (ft_strncmp((*fn_lst)->value, *temp,
// 				ft_strlen(*temp))))
// 	{
// 		*fn_lst = (*fn_lst)->next;
// 		return (NULL);
// 	}
// 	else
// 		temp++;
//     return ((*fn_lst)->value);
// }

void	fn_match_util(char **arr, t_files **fn_lst, t_files **result)
{
	char	*trimmed;
	char	**temp;

	int flag; // mark valid filenames with flag = 1
	temp = NULL;
	trimmed = NULL;
	flag = 0;
    t_files *cur = *fn_lst;
	while (cur) // iterate filename by filename calling ->next
	{
        // if (!initail_match(temp, arr, &cur, &flag))
        //     continue ;
		if_end_to_match(arr, &flag);
		temp = arr;
		if (temp[0][0] != '*' && (ft_strncmp((*fn_lst)->value, *temp,
					ft_strlen(*temp))))
		{
			// *fn_lst = (*fn_lst)->next;
            cur = cur->next;
			continue ;
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
			else if (*trimmed == '\0' && !temp++)
				flag = 1;
		}
		if (trimmed && trimmed[0] != '\0')
			if_flag(&flag, trimmed, *(temp - 1));
		update_result((cur)->value, result, &flag);
		// *fn_lst = (*fn_lst)->next;
        cur = cur->next;
	}
}

void	fn_match(t_files *fn_lst, char *value, t_files **result)
{
	char **arr;
	char **updated_arr;

	updated_arr = NULL;
	arr = ft_split(value, '*'); //*
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