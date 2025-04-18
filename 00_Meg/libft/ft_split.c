/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:34:11 by menwu             #+#    #+#             */
/*   Updated: 2024/10/09 16:59:45 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_substr(char const *s, char c)
{
	int	i;
	int	counter;
	int	in_substr;

	i = 0;
	counter = 0;
	in_substr = 0;
	if (!*s)
		return (0);
	if (s[i] == c)
		in_substr = 1;
	while (s[i])
	{
		if (s[i] == c && !in_substr)
		{
			counter++;
			in_substr = 1;
		}
		else if (s[i] != c)
			in_substr = 0;
		i++;
	}
	if (s[i - 1] != c)
		return (counter + 1);
	return (counter);
}

int	find_next_char(char const *s, char c, int n)
{
	int	t;

	t = n;
	while (s[t] == c)
		t++;
	while (s[t] != '\0')
	{
		if (s[t] != c)
			t++;
		else if (s[t] == c)
			break ;
	}
	return (t);
}

char	*create_substr(char const *s, char c, int m, int n)
{
	char	*temp;

	while (s[m] == c)
		m++;
	temp = ft_substr(s, m, n - m);
	if (!temp)
		return (NULL);
	return (temp);
}

char	**fill_result(char const *s, char c, int counter, int n)
{
	int		i;
	int		prev_n;
	char	**result;

	i = 0;
	result = (char **)malloc((counter + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < counter)
	{
		prev_n = n;
		n = find_next_char(s, c, n);
		result[i] = create_substr(s, c, prev_n, n);
		if (!result[i])
		{
			while (i-- > 0)
				free (result[i]);
			free (result);
			return (NULL);
		}
		i++;
	}
	if (counter == 0)
		*result = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		counter;
	int		n;
	char	**result;

	if (!s)
		return (NULL);
	counter = count_substr(s, c);
	n = 0;
	result = fill_result(s, c, counter, n);
	if (result == NULL)
		return (NULL);
	result[counter] = NULL;
	return (result);
}
/*
#include <stdio.h>
int	main(void)
{
	char x[] = "  This is           ii  ";
	char y = ' ';
	char **result;
	int i = 0;

	result = ft_split(x, y);	
	if(result == NULL)
		return 0;
	while (result[i])
	{
		printf("string no. %d : %s\n", i, result[i]);
		free (result[i]);
		i++;
	}
	free (result);
	return (0);
}
*/
