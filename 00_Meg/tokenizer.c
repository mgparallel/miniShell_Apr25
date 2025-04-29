// #include "minishell.h"

// char *get_token_type(char *str)
// {

// 	if (*str == '&')
// 		return ("VARIABLE");
	

// }

// // Funtion to create the token strcture
// // assign value and token_type
// t_token *create_token(char *start, char *end)
// {
// 	t_token *t;
// 	char *str;
// 	int i;
	
// 	i = 0;
// 	t = malloc(sizeof(t_token));
// 	if (!t)
// 		return (NULL);
// 	if (*end < *start)
// 		return (free(t), NULL);
// 	while (*end - *start)
// 	{
// 		str[i] = *start;
// 		start++;
// 	}
// 	if (*end == *start && i == 0)
// 		str[i] = *start;
// 	str[i++] = '\0';
// 	t->value = str;
// 	t->type = get_token_type(*str);
// 	return (t);
// }

// // Function to find the end of the token
// // return char * pointer

// char *token_end(char* str, char ch)
// {
// 	char *temp;

// 	if (!str || *str == '\0')
// 		return (NULL);
// 	temp = str;
// 	while (temp)
// 	{
// 		if (*temp == ch)
// 			return (&*temp); //need check
// 		temp++;
// 	}
// 	if (*str == '\0')
// 		return (NULL);
// 	return (NULL);
// }

// bool ch_is_space(char ch)
// {
// 	return (ch == ' ' || ch == '\t' || ch == '\n');
// }

// bool ch_is_special(char ch)
// {
//     return (ch == '>' || ch == '<' || ch == '|' || ch == '&' || ch == '$');
// }

// // Function to count how many tokens are there
// // delimiters: ' ', '\t', '\n', '<', '<<', '>', '>>', '|', '||', '&', '&&'
// int	count_token(char *input)
// {
// 	int count;
// 	int single_quote;
// 	int double_quote;
// 	char *temp;
//     int token_started;
	
// 	count = 0;
// 	single_quote = 0;
// 	double_quote = 0;
//     token_started = 0;
// 	temp = input;
// 	while (*temp)
// 	{
// 		if (*temp == '\'' && !double_quote)
//         {
// 			single_quote = !single_quote;
//             token_started = 1;
//         }
// 		else if (*temp == '"' && !single_quote)
//         {
// 			double_quote = double_quote;
//             token_started = 1;
//         }
// 		else if (!single_quote && !double_quote && (ch_is_space(*temp) || ch_is_special(*temp)))
// 		{
//             if (token_started)
// 			{
//                 count++;
//                 token_started = 0;
//             }
//             if (ch_is_special(*temp))
//             {
//                 if (*(temp + 1) ==  *temp)
//                 {
//                     count++;
//                     temp += 2;
//                     continue ;
//                 }
//                 else
//                 {
//                     count++;
//                     temp++;
//                     continue ;
//                 }
//             }
//         }
//         else
//             token_started = 1;
// 		temp++;
//     }
// 	if (token_started)
// 		count++;
// 	return (count);
// }

// // Funtion receive the user input and put them into tokens
// // Not finished!
// t_token **tokenizer(char *input)
// {
// 	char *token_start;
// 	int single_quote;
// 	int	double_quote;
// 	t_token **token;
// 	int i;

// 	token_start = NULL;
// 	single_quote = 0;
// 	double_quote = 0;
// 	i = 0;
// 	token = malloc(sizeof(t_token *) * (count_token(input) + 1));
// 	if (!token)
// 		return (NULL);
// 	while (*input)
// 	{
// 		if (*input == '\'' && !double_quote)
// 		{
// 			single_quote = !single_quote;
// 			if (token_start)
// 			{
// 				token[i] = create_token(token_start, *input);
// 				token_start = NULL;
// 				i++;
// 			}
// 			else
// 				token_start = *input;
// 		}
// 		else if (*input == '"' && !single_quote)
// 		{
// 			double_quote = !double_quote;
// 			if (token_start)
// 			{
// 				token[i] = create_token(token_start, *input);
// 				token_start = NULL;
// 				i++;
// 			}
// 			else
// 				token_start = *input;
// 		}
// 		else if (!single_quote && !double_quote && ch_is_space(*input))
// 		{
// 			if (!token_start)
// 			{
// 				input++;
// 				continue ;
// 			}
// 			else
// 			{
// 				token[i] = create_token(token_start, *input);
// 				token_start = NULL;
// 				i++;
// 			}
// 		}
// 		else if (!single_quote && !double_quote && ch_is_special(*input))
// 		{
// 			if (!token_start)
// 			{
// 				if (ch_is_special(*(input + 1) == *input))
// 				{
// 					input++;
// 					token[i] = create_token(*(input - 1), *input);
// 				}
// 				else
// 					token[i] = create_token(*input, *input);
// 				i++;
// 			}
// 		}
// 		else
// 			if (!token_start)
// 				token_start = *input;
// 		input++;
// 	}
// 	return (token);
// }