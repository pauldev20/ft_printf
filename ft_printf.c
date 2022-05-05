/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:19:52 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/05 12:46:05 by pgeeser          ###   ########.fr       */
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
	else if (c == '\0')
		return (1);
	return (0);
}

t_args	init_args(void)
{
	t_args	rtn;

	rtn.minus = 0;
	rtn.zero = 0;
	rtn.prec = -1;
	rtn.width = -1;
	rtn.space = 0;
	rtn.plus = 0;
	rtn.tag = 0;
	return (rtn);
}

t_args	parse_args(char **token)
{
	t_args	rtn;

	rtn = init_args();
	while (!is_token(**token))
	{
		if (**token == '#')
			rtn.tag = 1;
		if (**token == ' ')
			rtn.space = 1;
		if (**token == '+')
			rtn.plus = 1;
		if (**token == '0' && rtn.zero == 0)
			rtn.zero = 1;
		if (**token == '-')
			rtn.minus = 1;
		if (**token == '.')
		{
			rtn.prec = ft_atoi(*token + 1);
			if (ft_atoi(*token + 1) > 0)
				*token += ft_digits_of_int(ft_atoi(*token + 1));
		}
		else if (ft_isdigit(**token) && (**token != '0'))
		{
			rtn.width = ft_atoi(*token);
			if (ft_atoi(*token) > 0)
				*token += ft_digits_of_int(ft_atoi(*token)) - 1;
		}
		(*token)++;
	}
	return (rtn);
}

int	parse_token(char **token, va_list *ptr)
{
	int		i;
	t_args	args;

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
