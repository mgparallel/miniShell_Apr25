/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:04:01 by menwu             #+#    #+#             */
/*   Updated: 2024/10/17 22:31:31 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hexa_address_recursion(unsigned long ref_address, int inner_count)
{
	unsigned char	mold;
	const char		*base_hexa;

	base_hexa = "0123456789abcdef";
	if (!ref_address)
		return (0);
	if (ref_address >= 16)
		inner_count = hexa_address_recursion(ref_address / 16, ++inner_count);
	mold = ref_address % 16;
	write (1, &base_hexa[mold], 1);
	return (inner_count);
}

int	address_print(void *address)
{
	unsigned long	ref_address;
	int				inner_count;

	ref_address = (unsigned long)address;
	if (!ref_address)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	ref_address = (unsigned long)address;
	ft_putstr("0x");
	inner_count = 2;
	inner_count = hexa_address_recursion(ref_address, inner_count);
	return (inner_count + 1);
}
