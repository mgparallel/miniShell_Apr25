/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_add_node_to_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:18:29 by menwu             #+#    #+#             */
/*   Updated: 2025/07/06 22:32:38 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_to_lst(char *str, int *start, int *end, t_files **lst)
{
	t_files	*new_node;
	char	*node_value;

	node_value = ft_strndup(str + *start, *end - *start);
	if (!node_value)
		return (free_lst(lst));
	new_node = malloc(sizeof(t_files));
	if (!new_node)
		return (free(node_value), free_lst(lst));
	new_node->value = node_value;
	new_node->next = NULL;
	indir_lst_addback(lst, new_node);
	(*end)++;
	*start = *end;
}

void	add_expanded_var_to_lst(char *value, t_files **lst)
{
	t_files	*new_node;

	new_node = malloc(sizeof(t_files));
	if (!new_node)
		return (free_lst(lst));
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node), free_lst(lst));
	new_node->next = NULL;
	indir_lst_addback(lst, new_node);
}

int	copy_first_str(char **re, char **s1, int len1)
{
	int	i;

	i = 0;
	while (i < len1)
	{
		(*re)[i] = (*s1)[i];
		i++;
	}
	free(*s1);
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2, size_t len2)
{
	size_t	len1;
	size_t	i;
	size_t	j;
	char	*re;

	i = 0;
	j = 0;
	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	re = malloc(len1 + len2 + 1);
	if (!re)
		return (NULL);
	if (s1)
		i = copy_first_str(&re, &s1, len1);
	while (j < (size_t)len2)
		re[i++] = s2[j++];
	re[i] = '\0';
	return (re);
}
