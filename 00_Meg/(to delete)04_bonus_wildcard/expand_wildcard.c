/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:42:22 by menwu             #+#    #+#             */
/*   Updated: 2025/07/07 23:17:12 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	indir_lst_addback(t_files **lst, t_files *new)
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

void	create_fn_lst(struct dirent *dp, t_files **fn_lst)
{
	t_files	*new_token;

	new_token = malloc(sizeof(t_files));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(dp->d_name);
	if (!new_token->value)
		return ;
	new_token->next = NULL;
	indir_lst_addback(fn_lst, new_token);
}

void	fetch_wildcard(t_files **fn_lst)
{
	struct dirent	*dp;
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
	{
		printf("error opening directory");
		return ;
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

void	update_result(char *value, t_files **result, int *flag)
{
	t_files	*new;

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

void	if_end_to_match(char **arr, int *flag)
{
	char	**ref;
	char	*prev;

	ref = arr;
	prev = NULL;
	while (*ref)
	{
		prev = *ref;
		ref++;
	}
	if (!ft_strchr(prev, '*'))
		*flag = -1;
}

int	match_beginning(char **temp, char **arr, t_files **fn_lst)
{
	temp = arr;
	if (temp[0][0] != '*')
	{
		if (ft_strncmp((*fn_lst)->value, *temp, ft_strlen(*temp)))
		{
			*fn_lst = (*fn_lst)->next;
			return (0);
		}
	}
	else
		temp++;
	return (1);
}

void	update_trimmed(int *flag, char **trimmed, char **temp)
{
	if (*trimmed && *trimmed[0] != '\0')
	{
		if (*flag != -1)
			*flag = 1;
		else
		{
			*trimmed = *trimmed + ft_strlen(*trimmed) - ft_strlen(*(temp - 1));
			if (!ft_strcmp(*trimmed, *(temp - 1)))
				*flag = 1;
		}
	}
}

int	parse_temp(char **trimmed, char **temp, char **arr, int *flag)
{
	*trimmed = str_match(*trimmed, *(temp - 1));
	if (!*trimmed)
	{
		if (arr[0][0] == '*' && !temp++)
			*flag = 1;
		return (0); //break
	}
	else if (*trimmed[0] == '\0')
	{
		if (!temp++)
			*flag = 1;
	}
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
		if (!match_beginning(temp, arr, fn_lst))
			continue ;
		trimmed = (*fn_lst)->value;
		while (*++temp)
		{
            if (!parse_temp(&trimmed, temp, arr, &flag))
                break ;
		}
		update_trimmed(&flag, &trimmed, temp);
		update_result((*fn_lst)->value, result, &flag);
		*fn_lst = (*fn_lst)->next;
	}
}

bool	if_wildcard(t_token **cur_token)
{
	char	*str;
	char	*pos;

	str = (*cur_token)->value;
	pos = ft_strchr(str, '*');
	if (!pos)
		return (false);
	(*cur_token)->type = WILDCARD;
	return (true);
}

int	expand_wildcard(t_token **lst, t_token **cur_token)
{
	t_files	*fn_lst;
	t_files	*result;

	fn_lst = NULL;
	result = NULL;
	fetch_wildcard(&fn_lst);
	if (!fn_lst)
		return (printf("Failed fetching file names\n"), -1);
	fn_match(fn_lst, (*cur_token)->value, &result);
	if (!result)
	{
		(*cur_token)->type = WORD;
		return (0);
	}
	add_wildcard_token(lst, *cur_token, result);
	return (0);
}
