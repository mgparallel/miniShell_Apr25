/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:32:24 by menwu             #+#    #+#             */
/*   Updated: 2024/10/18 00:40:21 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_htoa(unsigned int n, int print_count, char ch)
{
	int				mol;
	unsigned long	nrb;
	const char		*base_hexa;
	const char		*base_hexa_mayus;

	nrb = n;
	base_hexa = "0123456789abcdef";
	base_hexa_mayus = "0123456789ABCDEF";
	if (nrb >= 16)
		print_count = ft_htoa(nrb / 16, ++print_count, ch);
	mol = nrb % 16;
	if (ch == 'x')
		write (1, &base_hexa[mol], 1);
	else
		write (1, &base_hexa_mayus[mol], 1);
	return (print_count);
}
