/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:11:42 by menwu             #+#    #+#             */
/*   Updated: 2025/07/05 07:30:54 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_type_var_util(char *var, t_files *env, t_token **cur_token, t_token **lst)
{
    char *expand_value;
    int if_space;

    if_space = 0;
    expand_value = get_var_value(var, env);
	free(var);
    if (!expand_value)
    {
        if_space = lst_rm_token(lst, cur_token);
        if ((*cur_token) && (*cur_token)->has_leading_space == 0)
            (*cur_token)->has_leading_space = if_space;
        return (1);
    }
    else
    {
		if ((*cur_token)->value)
        	free((*cur_token)->value);
        (*cur_token)->value = expand_value;
    }
    (*cur_token)->type = ARG;
    return (1);
}

int if_symbol_after_dollar(t_token **cur_token, t_token **lst)
{
        if (*cur_token && ((*cur_token)->next->type == SINGLE_QUOTE 
                                    || (*cur_token)->next->type == DOUBLE_QUOTE))
		{
			lst_rm_token(lst, cur_token);
			return (1);
		}
		(*cur_token)->type = ARG;
		return (0);
}

int parse_type_var(t_token **lst, t_token **cur_token, t_files *env)
{
    char *var;
    char *pos; //pointer where var ends as finding NOT-{0-9a-zA-Z_}
	char *end_brace;

    var = NULL;
	end_brace = NULL;
    if (if_exit_code(cur_token))
        return (0);
    pos = (*cur_token)->value + 1; //${USER}
	if (*pos == '\0'|| *pos == '+' || *pos == '=')
		return (if_symbol_after_dollar(cur_token, lst));
	if (*pos == '{')
	{
		end_brace = ft_strchr(pos, '}');
		if (!end_brace)
			return (printf("Syntex error: Non closing braces"), -1);
		var = ft_strcpy(pos + 1, end_brace);
		if (!var)
			return (printf("Malloc failed"), -1);
		pos = end_brace + 1;
	}
	if (!var) //no braces
	{
		var = ft_strdup(pos);
		if (!var)
        	return (printf("Malloc failed"), -1); //changed
		while (if_alnum_underscore_braces(*pos))
        	pos++;
	}
    if (*pos != '\0') //we seperate into 2 tokens: VAR and WORD
    {
            if (update_token(lst, (*cur_token)->value, pos, WORD) == -1)
				return (-1);
			free(var);
            var = ft_strcpy((*cur_token)->value + 1, pos);
            if (!var)
                return (printf("Malloc failed"), -1);
    }
	return (parse_type_var_util(var, env, cur_token, lst));
}


// void if_braces(char **var) //{USER}
// {
//     char *pos;
// 	char *temp;
// 	char *original;

//     pos = NULL;
// 	temp = NULL;
// 	original = *var;
// 	printf("ori: %s\n", original);
//     if (*var[0] == '{')
//     {
//         pos = ft_strchr(*var, '}');
//         if (!pos)
//             return ; //error code
//         else if (*(pos + 1) == '\0')
//         {
//             temp = ft_strcpy(*var + 1, pos);
//             if (!temp)
//                 return ;
// 			*var = temp;
// 			// free(original);
//         }
//     }
// 	printf("afetr: %s\n", *var);
// }

// function to check if ENV_VAR are valid
// int parse_type_var(t_token **lst, t_token **cur_token, t_files *env)
// {
//     char *var;
//     char *pos; //pointer where var ends as finding NOT-{0-9a-zA-Z_}

//     var = NULL;
//     if (if_exit_code(cur_token))
//         return (0);
//     pos = (*cur_token)->value + 1; //USER$?
// 	if (*pos == '\0'|| *pos == '+' || *pos == '=')
// 		return (if_symbol_after_dollar(cur_token, lst));
//     while (if_alnum_underscore_braces(*pos))
//         pos++;
//     if (*pos != '\0') //we seperate into 2 tokens: VAR and WORD
//     {
//             update_token(lst, (*cur_token)->value, pos, WORD);
//             var = ft_strcpy((*cur_token)->value + 1, pos);
//             if (!var)
//                 return (0);
//     }
//     else
//     {
// 		var = ft_strdup((*cur_token)->value + 1);
// 		if (!var)
//         	return (1);
// 	}
//     if_braces(&var);
// 	return (parse_type_var_util(var, env, cur_token, lst));
// }