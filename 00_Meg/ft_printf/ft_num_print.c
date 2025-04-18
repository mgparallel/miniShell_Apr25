/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:07:00 by menwu             #+#    #+#             */
/*   Updated: 2024/10/17 23:53:31 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_itoa(int n, int print_count)
{
	long	nrb;
	char	mold;

	nrb = n;
	if (nrb < 0)
	{
		write (1, "-", 1);
		nrb *= -1;
		print_count++;
	}
	if (nrb > 9)
		print_count = ft_itoa(nrb / 10, ++print_count);
	mold = nrb % 10 + '0';
	write (1, &mold, 1);
	return (print_count);
}

int	ft_uitoa(unsigned int n, int print_count)
{
	long	nrb;
	char	mold;

	nrb = n;
	if (nrb > 9)
		print_count = ft_uitoa(nrb / 10, ++print_count);
	mold = nrb % 10 + '0';
	write (1, &mold, 1);
	return (print_count);
}
