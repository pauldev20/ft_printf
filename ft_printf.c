/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:19:52 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/04 11:01:10 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"
#include <stdarg.h>

#include <stdio.h>

int	is_token(char c)
{
	if (c == 'c' || c == 's' || c == 'p')
		return (1);
	else if (c == 'd' || c == 'i' || c == 'u')
		return (1);
	else if (c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

// 0000 0000 prec prec prec prec - 0? 0? width width width width + space 0x
long	parse_args(char **token)
{
	long	rtn;

	rtn = 0;
	while (!is_token(**token))
	{
		if (**token == '#')
			rtn += 0b0001 << 0;
		if (**token == ' ')
			rtn += 0b0001 << 4;
		if (**token == '+')
			rtn += 0b0001 << 8;
		if (**token == '0' && !(rtn >> 44 & 0b11111111))
			rtn += (long)'0' << 44;
		else if (!(rtn >> 44 & 0b11111111))
			rtn += (long)' ' << 44;
		if (**token == '-')
			rtn += (long)0b0001 << 52;
		if (**token == '.')
		{
			rtn += (long)ft_atoi(*token + 1) << 56;
			*token += ft_digits_of_int(ft_atoi(*token + 1));
		}
		else if (ft_isdigit(**token) && (**token != '0'))
		{
			rtn += (long)ft_atoi(*token) << 12;
			*token += ft_digits_of_int(ft_atoi(*token)) - 1;
		}
		(*token)++;
	}
	return (rtn);
}

int	parse_token(char **token, va_list *ptr)
{
	int		i;
	long	args;

	i = 0;
	args = parse_args(token);
	if (**token == 'c')
		i = printchar((char)va_arg(*ptr, int), args);
	else if (**token == 's')
		i = printstr(va_arg(*ptr, char *), args);
	else if (**token == 'p')
		i = printptr(va_arg(*ptr, void *), args);
	else if (**token == 'd' || **token == 'i')
		i = printnbr(va_arg(*ptr, int), args);
	else if (**token == 'u')
		i = printnbr(va_arg(*ptr, unsigned int), args);
	else if (**token == 'x')
		i = printhex(va_arg(*ptr, unsigned int), 'a', args);
	else if (**token == 'X')
		i = printhex(va_arg(*ptr, unsigned int), 'A', args);
	else if (**token == '%')
		i = putchr('%');
	(*token)++;
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str++ == '%')
			i += parse_token((char **)&str, &args);
		else
			i += ft_putchar_fd(*(str - 1), 1);
	}
	va_end(args);
	return (i);
}
