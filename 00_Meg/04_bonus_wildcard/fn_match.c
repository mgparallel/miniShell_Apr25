/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:45:04 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 01:26:32 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*initail_match(char **temp, t_files **fn_lst)
{
	if (temp[0][0] != '*' && (ft_strncmp((*fn_lst)->value, *temp,
				ft_strlen(*temp))))
	{
		*fn_lst = (*fn_lst)->next;
		return (NULL);
	}
	else
		return ((*fn_lst)->value);
}

int	check_trimmed(char *trimmed, char **temp, char **arr, int *flag)
{
	if (!trimmed)
	{
		if (arr[0][0] == '*' && !temp++)
			*flag = 1;
		return (0);
	}
	else if (*trimmed == '\0' && !temp++)
		*flag = 1;
	return (1);
}

void	fn_match_util(char **arr, t_files **fn_lst, t_files **result)
{
	char	*trimmed;
	char	**temp;
	int		flag;

	temp = NULL;
	trimmed = NULL;
	flag = 0;
	while (*fn_lst)
	{
		if_end_to_match(arr, &flag);
		temp = arr;
		trimmed = initail_match(temp, fn_lst);
		if (!trimmed)
			continue ;
		temp++;
		while (*++temp)
			trimmed = strmatch(trimmed, *(temp - 1));
		if (trimmed && trimmed[0] != '\0')
			if_flag(&flag, trimmed, *(temp - 1));
		update_result((*fn_lst)->value, result, &flag);
		*fn_lst = (*fn_lst)->next;
	}
}

void	fn_match(t_files *fn_lst, char *value, t_files **result)
{
	char	**arr;
	char	**updated_arr;

	updated_arr = NULL;
	arr = ft_split(value, '*');
	if (!arr)
		return ;
	if (!ft_strcmp(value, "*"))
	{
		*result = fn_lst;
		return ;
	}
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

// void	fn_match_util(char **arr, t_files **fn_lst, t_files **result)
// {
// 	char	*trimmed;
// 	char	**temp;

// 	int flag; // mark valid filenames with flag = 1
// 	temp = NULL;
// 	trimmed = NULL;
// 	flag = 0;
// 	while (*fn_lst) // iterate filename by filename calling ->next
// 	{
// 		if_end_to_match(arr, &flag);
// 		temp = arr;
// 		trimmed = initail_match(temp, fn_lst);
// 		if (!trimmed)
// 			continue ;
// 		temp++;
// 		while (*++temp)
// 		{
// 			trimmed = strmatch(trimmed, *(temp - 1));
// 			if (!check_trimmed(trimmed, temp, arr, &flag))
// 				break ;
// 		}
// 		if (trimmed && trimmed[0] != '\0')
// 			if_flag(&flag, trimmed, *(temp - 1));
// 		update_result((*fn_lst)->value, result, &flag);
// 		*fn_lst = (*fn_lst)->next;
// 	}
// }