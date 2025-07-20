/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:33:36 by menwu             #+#    #+#             */
/*   Updated: 2024/10/07 15:33:46 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	write_recursive(int n, int fd)
{
	char	new;

	if (n > 9)
	{
		write_recursive(n / 10, fd);
	}
	new = n % 10 + '0';
	write (fd, &new, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	else if (n == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	write_recursive(n, fd);
}
/*
int	main(void)
{
	int x = -1234;
	int y = -2147483648;
	int z = 2147483647;
	int m = 0;

	ft_putnbr_fd(x, 1);
	write (1, "\n", 1);
	ft_putnbr_fd(y, 1);
	write (1, "\n", 1);
	ft_putnbr_fd(z, 1);
	write (1, "\n", 1);
	ft_putnbr_fd(m, 1);

	return (0);
}
*/
