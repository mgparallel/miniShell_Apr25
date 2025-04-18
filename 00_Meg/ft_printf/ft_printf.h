/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:35:53 by menwu             #+#    #+#             */
/*   Updated: 2024/10/17 23:26:44 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_strlen(char *str);
int	ft_putchar(int chr);
int	ft_putstr(char *str);
int	address_print(void *address);
int	ft_htoa(unsigned int n, int print_count, char ch);
int	ft_itoa(int n, int print_count);
int	ft_uitoa(unsigned int n, int print_count);
int	ft_printf(char const *s, ...);

#endif
