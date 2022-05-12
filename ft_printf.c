/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:19:52 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/12 11:44:22 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

t_args	parse_args(char **token, t_args args)
{
	while (!is_token(**token))
	{
		if (**token == '#')
			args.tag = 1;
		if (**token == ' ')
			args.space = 1;
		if (**token == '+')
			args.plus = 1;
		if (**token == '0' && args.zero == 0)
			args.zero = 1;
		if (**token == '-')
			args.minus = 1;
		if (ft_isdigit(**token) && (**token != '0'))
			args.width = ft_atoi(*token);
		if (ft_isdigit(**token) && (**token != '0') && ft_atoi(*token) > 0)
			*token += ft_digits_of_int(ft_atoi(*token)) - 1;
		if (**token == '.')
			args.prec = ft_atoi(*token + 1);
		if (**token == '.' && ft_atoi(*token + 1) > 0)
			*token += ft_digits_of_int(ft_atoi(*token + 1));
		(*token)++;
	}
	return (args);
}

int	parse_token(char **token, va_list *ptr)
{
	int		i;
	t_args	args;

	i = 0;
	args = parse_args(token, init_args());
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
	else if (**token == 'x' || **token == 'X')
		i = printhex(va_arg(*ptr, unsigned int), **token - 23, args);
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
			i += putchr(*(str - 1));
	}
	va_end(args);
	return (i);
}
