/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:19:52 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/17 15:03:08 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_token(char **token, va_list *ptr)
{
	int		i;

	i = 0;
	if (**token == 'c')
		i = putchr((char)va_arg(*ptr, int));
	else if (**token == 's')
		i = putstr(va_arg(*ptr, char *));
	else if (**token == 'p')
		i = puthex((unsigned long long)va_arg(*ptr, void *), 'a', 1);
	else if (**token == 'd' || **token == 'i')
		i = putnbr(va_arg(*ptr, int));
	else if (**token == 'u')
		i = putnbr(va_arg(*ptr, unsigned int));
	else if (**token == 'x' || **token == 'X')
		i = puthex(va_arg(*ptr, unsigned int), **token - 23, 0);
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
