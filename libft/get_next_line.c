/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapujol- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:35:05 by gapujol-          #+#    #+#             */
/*   Updated: 2025/01/29 15:25:11 by gapujol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

#include "libft.h"

static void	*free_res(char **res)
{
	free(*res);
	*res = NULL;
	return (NULL);
}

static char	*copy_buffer(char *buffer, char *str)
{
	char	*aux;
	char	*res;
	int		end;

	end = 0;
	while (buffer[end] && buffer[end] != '\n')
		end++;
	if (str)
	{
		aux = ft_substr(buffer, 0, end + 1);
		res = ft_strjoin(str, aux);
		free(str);
		free(aux);
	}
	else
		res = ft_substr(buffer, 0, end + 1);
	ft_strlcpy(buffer, buffer + end + 1, ft_strlen(buffer + end) + 1);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*res;

	if (fd < 0)
		return (NULL);
	bytes_read = 1;
	res = NULL;
	while (bytes_read > 0)
	{
		if (buffer[fd][0])
		{
			res = copy_buffer(buffer[fd], res);
			if (!res)
				return (NULL);
			if (ft_strchr(res, '\n'))
				return (res);
		}
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_res(&res));
		buffer[fd][bytes_read] = '\0';
	}
	return (res);
}
/*
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int	fd1;
	int	fd2;
	char	*line;

	//line = get_next_line(0);
	//printf("file1: %s", line);
	fd1 = open("get_next_line.c", O_RDONLY);
//	fd2 = open("file4.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd1);
		printf("file1: %s", line);
//		line = get_next_line(fd2);
//		printf("file2: %s", line);
		if (!line)
			break;
	}
}*/
