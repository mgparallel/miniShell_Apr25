#include "minishell.h"

// Funtion to create the token stricture
// assign value and token_type
void create_token(char *start, char *end, t_token *token)
{

}


// Function to find the end of the token
// return char * pointer

char *token_end(char* str, char ch)
{
	char *temp;

	if (!str || *str == '\0')
		return (NULL);
	temp = str;
	while (temp)
	{
		if (*temp == ch)
			return (&*temp); //need check
		temp++;
	}
	if (*str == '\0')
		return (NULL);
	return (NULL);
}

bool ch_is_space(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n');
}

bool ch_is_special(char ch)
{
    return (ch == '>' || ch == '<' || ch == '|' || ch == '&');
}

// Function to count how many tokens are there
// delimiters: ' ', '\t', '\n', '<', '<<', '>', '>>', '|', '||', '&', '&&'
int	count_token(char *input)
{
	int count;
	int single_quote;
	int double_quote;
	char *temp;
    int token_started;
	
	count = 0;
	single_quote = 0;
	double_quote = 0;
    token_started = 0;
	temp = input;
	while (*temp)
	{
		if (*temp == '\'' && !double_quote)
        {
			single_quote = !single_quote;
            token_started = 1;
            temp++;
        }
		else if (*temp == '"' && !single_quote)
        {
			double_quote = double_quote;
            token_started = 1;
            temp++;
        }
		else if (!single_quote && !double_quote && (ch_is_space(*temp) || ch_is_special(*temp)))
		{
            if (token_started)
			{
                count++;
                token_started = 0;
            }
            if (ch_is_special(*temp))
            {
                if (*(temp + 1) ==  *temp)
                {
                    count++;
                    temp += 2;
                    continue ;
                }
                else
                {
                    count++;
                    temp++;
                    continue ;
                }
            }
            temp++;
        }
        else
        {
                token_started = 1;
                temp++;
        }   
    }
	if (token_started)
		count++;
	return (count);
}

// Funtion receive the user input and put them into tokens
// Not finished!
t_token *tokenizer(char *input)
{
	char *token_start;
	char *token_end;
	t_token *token;
	int in_token;
	int count;

	in_token = 0;
	count = count_token(input);
	token = malloc(sizeof(t_token) * (count + 1)); //not sure if need to +1
	if (!token)
		return (NULL);
	while (*input)
	{

	}
	return (token);
}