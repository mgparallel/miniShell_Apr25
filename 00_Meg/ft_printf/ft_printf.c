/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:36:35 by menwu             #+#    #+#             */
/*   Updated: 2024/10/17 23:24:43 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_type(va_list ap, char ch)
{
	int	print_count;

	print_count = 0;
	if (ch == 'c')
		print_count = ft_putchar(va_arg(ap, int));
	else if (ch == 's')
		print_count = ft_putstr(va_arg(ap, char *));
	else if (ch == 'p')
		print_count = address_print(va_arg(ap, void *));
	else if (ch == 'd' || ch == 'i')
		print_count = ft_itoa(va_arg(ap, int), print_count + 1);
	else if (ch == 'u')
		print_count = ft_uitoa(va_arg(ap, unsigned int), print_count + 1);
	else if (ch == 'x' || ch == 'X')
		print_count = ft_htoa(va_arg(ap, unsigned int), print_count + 1, ch);
	else if (ch == '%')
	{
		print_count = 1;
		ft_putchar('%');
	}
	return (print_count);
}

int	ft_printf(char const *s, ...)
{
	va_list	ap;
	int		count;
	int		i;

	count = 0;
	i = -1;
	va_start(ap, s);
	if (!s)
		return (0);
	while (s[++i])
	{
		if (s[i] == '%' && s[i + 1] != '\0')
		{
			i++;
			count += check_type(ap, s[i]);
		}
		else if (s[i] == '%')
			return (-1);
		else
		{
			ft_putchar(s[i]);
			count++;
		}
	}
	return (count);
}
