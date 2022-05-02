/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:19:52 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/26 17:40:12 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "./libft/libft.h"
#include <stdarg.h>

int	putstr(char *s, int fd)
{
	if (s)
		return (ft_putstr_fd(s, fd));
	return (ft_putstr_fd("(null)", fd));
}

int	parse_token(char **tokenstr, va_list *ptr)
{
	int	i;

	i = 0;
	if ((*tokenstr)[1] == 'c')
		i = ft_putchar_fd((char)va_arg(*ptr, int), 1);
	else if ((*tokenstr)[1] == 's')
		i = putstr(va_arg(*ptr, char *), 1);
	else if ((*tokenstr)[1] == 'p')
		i = ft_putptr_fd(va_arg(*ptr, void *), 1);
	else if ((*tokenstr)[1] == 'd')
		i = ft_putnbr_fd(va_arg(*ptr, int), 1);
	else if ((*tokenstr)[1] == 'i')
		i = ft_putnbr_fd(va_arg(*ptr, int), 1);
	else if ((*tokenstr)[1] == 'u')
		i = ft_putnbr_uns_fd(va_arg(*ptr, unsigned int), 1);
	else if ((*tokenstr)[1] == 'x')
		i = ft_puthex_fd(va_arg(*ptr, unsigned int), 1, 'a');
	else if ((*tokenstr)[1] == 'X')
		i = ft_puthex_fd(va_arg(*ptr, unsigned int), 1, 'A');
	else if ((*tokenstr)[1] == '%')
		i = ft_putchar_fd('%', 1);
	(*tokenstr)++;
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
