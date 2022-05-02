/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:19:52 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/02 17:44:27 by pgeeser          ###   ########.fr       */
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

// 0000 0000 0000 0000 0000 0000 0000 0000 0000 width width width width + space 0x
long	parse_args(char **token, va_list *ptr)
{
	long	rtn;

	rtn = 0;
	while (!is_token((*token)[1]))
	{
		if ((*token)[1] == '#')
			rtn += 0b0001 << 0;
		if ((*token)[1] == ' ')
			rtn += 0b0001 << 4;
		if ((*token)[1] == '+')
			rtn += 0b0001 << 8;
		if ((*token)[1] == '0')
			rtn += (long)0b0001 << 44;
		if ((*token)[1] == '.')
		{
			(*token) += 2;
			rtn += (long)ft_atoi(*token) << 12;
			while (ft_isdigit(**token))
				(*token)++;
			(*token) -= 2;
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
	args = parse_args(token, ptr);
	if ((*token)[1] == 'c')
		i = ft_putchar((char)va_arg(*ptr, int));
	else if ((*token)[1] == 's')
		i = putstr(va_arg(*ptr, char *));
	else if ((*token)[1] == 'p')
		i = putptr(va_arg(*ptr, void *));
	else if ((*token)[1] == 'd' || (*token)[1] == 'i')
		i = putnbr(va_arg(*ptr, int), args);
	else if ((*token)[1] == 'u')
		i = putnbr(va_arg(*ptr, unsigned int), args);
	else if ((*token)[1] == 'x')
		i = puthex(va_arg(*ptr, unsigned int), 'a', args);
	else if ((*token)[1] == 'X')
		i = puthex(va_arg(*ptr, unsigned int), 'A', args);
	else if ((*token)[1] == '%')
		i = ft_putchar('%');
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
		if (*str == '%')
			i += parse_token((char **)&str, &args);
		else
			i += ft_putchar_fd(*str, 1);
		str++;
	}
	va_end(args);
	return (i);
}
