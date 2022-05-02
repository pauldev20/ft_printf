/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:19:52 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/02 12:38:14 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"
#include <stdarg.h>

int	parse_token(char **token, va_list *ptr)
{
	int	i;

	i = 0;
	if ((*token)[1] == 'c')
		i = putchar((char)va_arg(*ptr, int));
	else if ((*token)[1] == 's')
		i = putstr(va_arg(*ptr, char *));
	else if ((*token)[1] == 'p')
		i = putptr(va_arg(*ptr, void *));
	else if ((*token)[1] == 'd' || (*token)[1] == 'i')
		i = ft_putnbr_fd(va_arg(*ptr, int), 1);
	else if ((*token)[1] == 'u')
		i = ft_putnbr_uns_fd(va_arg(*ptr, unsigned int), 1);
	else if ((*token)[1] == 'x')
		i = ft_puthex_fd(va_arg(*ptr, unsigned int), 1, 'a');
	else if ((*token)[1] == 'X')
		i = ft_puthex_fd(va_arg(*ptr, unsigned int), 1, 'A');
	else if ((*token)[1] == '%')
		i = ft_putchar_fd('%', 1);
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
