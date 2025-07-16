/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <gapujol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:58:07 by gapujol-          #+#    #+#             */
/*   Updated: 2025/07/12 22:01:05 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_code(const char *str, const char *status_str)
{
    int		count;
    int		i;
    size_t	len_status;
	char	*new_str;
	
	count = 0;
	i = 0;
	len_status = ft_strlen(status_str);
	while (str[i])
    {
        if (str[i] == '$' && str[i + 1] == '?')
        {
            count++;
            i += 2;
        }
        else
            i++;
    }
    if (count == 0)
        return (ft_strdup(str));
    new_str = malloc(ft_strlen(str) + count * (len_status - 2) + 1);
    if (!new_str)
        return (NULL);
    i = 0;
    while (*str)
    {
        if (*str == '$' && *(str + 1) == '?')
        {
            ft_memcpy(&new_str[i], status_str, len_status);
            i += len_status;
            str += 2;
        }
        else
            new_str[i++] = *str++;
    }
    new_str[i] = '\0';
    return (new_str);
}

void	expand_pipeline_exit_status(t_cmd *cmd, int exit_status)
{
    char	*status_str;
	char	*tmp;
	t_redir *r;
	int		i;

	status_str = ft_itoa(exit_status);
    while (cmd)
    {
		i = -1;
        while (++i < cmd->argc)
		{
			tmp = cmd->argv[i];
            cmd->argv[i] = expand_exit_code(tmp, status_str);
			free(tmp);
		}
        r = cmd->redir_list;
        while (r)
        {
			if (r->type != REDIR_HEREDOC)
			{
				tmp = r->filename;
            	r->filename = expand_exit_code(tmp, status_str);
				free(tmp);
			}
            r = r->next;
        }
		if (cmd->connector != PIPE)
        	break;
        cmd = cmd->next;
    }
    free(status_str);
}