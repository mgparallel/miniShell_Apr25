#include "minishell.h"

bool ch_is_space(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n');
}

bool ch_is_special(char ch)
{
    return (ch == '>' || ch == '<' || ch == '|' || ch == '&');
}

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*ref;

	if (lst == NULL)
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

char *ft_strcpy(char *start, char *end)
{
	int i;
	int len;
	char *result;

	i = 0;
	len = end - start;
	if (len < 0)
		return (NULL);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = *start;
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

// Funtion to create the token string and add it to the list
// assign value and token_type
void create_token(char **start, char *end, t_token_type type, t_token **lst)
{
	t_token *new_token;
	char *str;

	str = ft_strcpy(*start, end);
	if (!str)
	{
		//lstadd_back(lst, NULL);
		return ;
	}
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = str;
	new_token->type = type;
	new_token->lst = NULL;
	new_token->next = NULL;
	if (ch_is_space(*(*start - 1)))
		new_token->has_leading_space = 1;
	else
		new_token->has_leading_space = 0;
	lstadd_back(lst, new_token);
	*start = NULL; //reset the start point
}