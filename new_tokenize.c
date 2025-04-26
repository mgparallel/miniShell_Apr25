#include "minishell.h"

bool ch_is_space(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n');
}

bool ch_is_special(char ch)
{
    return (ch == '>' || ch == '<' || ch == '|' || ch == '&' || ch == '$');
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
	int arr[1024]; // an array of intergers to track the start and end of the token
	int i;
	
	count = 0;
	single_quote = 0;
	double_quote = 0;
    token_started = 0;
	temp = input;
	ft_bzero(arr, 1024);
	i = 0;
	while (*temp)
	{
		if (*temp == '\'' && !double_quote)
        {
			single_quote = !single_quote;
            token_started = 1;
			arr[i] = *temp - *input;
			i++;
        }
		else if (*temp == '"' && !single_quote)
        {
			double_quote = double_quote;
            token_started = 1;
			arr[i] = *temp - *input;
			i++;
        }
		else if (!single_quote && !double_quote && (ch_is_space(*temp) || ch_is_special(*temp)))
		{
            if (token_started)
			{
                count++;
                token_started = 0;
				arr[i] = *temp - *input;
				i++;
            }
            if (ch_is_special(*temp))
            {
                if (*(temp + 1) ==  *temp)
                {
					arr[i] = *temp - *input;
					arr[i++] = arr[i] + 1;
                    count++;
                    temp += 2;
					i++;
                    continue ;
                }
				else if(*temp == '$')
				{
					if (*(temp + 1) == '{')
					{
						token_started = 1;
						
					}
				}
                else
                {
					arr[i] = *temp - *input;
					arr[i++] = arr[i];
                    count++;
                    temp++;
					i++;
                    continue ;
                }
            }
        }
        else
            token_started = 1;
		temp++;
    }
	if (token_started)
		count++;
	return (count);
}

// Funtion receive the user input and put them into tokens
// Not finished!
t_token **tokenizer(char *input)
{
	char *token_start;
	int single_quote;
	int	double_quote;
	t_token **token;
	int i;

	token_start = NULL;
	single_quote = 0;
	double_quote = 0;
	i = 0;
	token = malloc(sizeof(t_token *) * (count_token(input) + 1));
	if (!token)
		return (NULL);
	while (*input)
	{
		if (*input == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			if (token_start)
			{
				token[i] = create_token(token_start, *input);
				token_start = NULL;
				i++;
			}
			else
				token_start = *input;
		}
		else if (*input == '"' && !single_quote)
		{
			double_quote = !double_quote;
			if (token_start)
			{
				token[i] = create_token(token_start, *input);
				token_start = NULL;
				i++;
			}
			else
				token_start = *input;
		}
		else if (!single_quote && !double_quote && ch_is_space(*input))
		{
			if (!token_start)
			{
				input++;
				continue ;
			}
			else
			{
				token[i] = create_token(token_start, *input);
				token_start = NULL;
				i++;
			}
		}
		else if (!single_quote && !double_quote && ch_is_special(*input))
		{
			if (!token_start)
			{
				if (ch_is_special(*(input + 1) == *input))
				{
					input++;
					token[i] = create_token(*(input - 1), *input);
				}
				else
					token[i] = create_token(*input, *input);
				i++;
			}
		}
		else
			if (!token_start)
				token_start = *input;
		input++;
	}
	return (token);
}