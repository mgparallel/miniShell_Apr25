/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:45:04 by menwu             #+#    #+#             */
/*   Updated: 2025/07/12 17:56:51 by menwu            ###   ########.fr       */
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

t_files *duplicate_fn_lst(t_files *lst)
{
    t_files *new_head = NULL;
    t_files *new_node = NULL;
    t_files *tail = NULL;

    while (lst)
    {
        new_node = malloc(sizeof(t_files));
        if (!new_node)
        {
            free_fn(&new_head);
            return NULL;
        }
        new_node->value = ft_strdup(lst->value);
        if (!new_node->value)
        {
            free(new_node);
            free_fn(&new_head);
            return NULL;
        }
        new_node->next = NULL;

        if (!new_head)
            new_head = new_node;
        else
            tail->next = new_node;
        tail = new_node;

        lst = lst->next;
    }
    return new_head;
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
		*result = duplicate_fn_lst(fn_lst);
		free_arr(arr);
		return ;
	}
	if (!*arr || *value == '*')
		updated_arr = prepend_arr(arr, value);
	else if (value[ft_strlen(value) - 1] == '*')
		updated_arr = append_arr(arr);
	else
		updated_arr = arr;
	fn_match_util(updated_arr, &fn_lst, result);
	if (updated_arr != arr)
    	free_arr(updated_arr);
	free_arr(arr);
}
	
