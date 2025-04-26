#include "minishell.h"

char *get_token_type(char *str)
{

	if (*str == '&')
		return ("VARIABLE");
	

}

// Funtion to create the token strcture
// assign value and token_type
t_token *create_token(char *start, char *end)
{
	t_token *t;
	char *str;
	int i;
	
	i = 0;
	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	if (*end < *start)
		return (free(t), NULL);
	while (*end - *start)
	{
		str[i] = *start;
		start++;
	}
	if (*end == *start && i == 0)
		str[i] = *start;
	str[i++] = '\0';
	t->value = str;
	t->type = get_token_type(*str);
	return (t);
}