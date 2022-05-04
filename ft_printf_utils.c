/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:32:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/04 17:55:39 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft/libft.h"
#include "ft_printf.h"

#include <stdio.h>

int	printnbr(long long nb, t_args args)
{
	int	i;

	if (args.minus)
	{
		i = putnbr(nb, args.prec, args.plus, args.space);
		while (i++ < (args.width))
			putchr(args.zero);
		return (i - 1);
	}
	else
	{
		i = 0;
		if (args.zero == '0')
			return (putnbr(nb, args.width - (nb < 0), args.plus, args.space));
		while (ft_digits_of_int(nb) + (nb < 0) + args.plus + ((args.prec
					- ft_digits_of_int(nb)) * (args.prec
					- ft_digits_of_int(nb))) + i++ < args.width)
			putchr(' ');
		i += putnbr(nb, args.prec, args.plus, args.space);
		return (i - 1);
	}
}

int	printchar(char c, t_args args)
{
	int	i;

	if (args.minus)
	{
		i = putchr(c);
		while (i++ < args.width)
			putchr(' ');
		return (i - 1);
	}
	else
	{
		i = 0;
		while (1 + i++ < args.width)
			putchr(' ');
		i += putchr(c);
		return (i - 1);
	}
}

int	printstr(char *s, t_args args)
{
	int	i;

	if (args.minus)
	{
		i = putstr(s, args.prec);
		while (i++ < args.width)
			putchr(' ');
		return (i - 1);
	}
	else
	{
		i = 0;
		while (s && ((int)ft_strlen(s) + i++ < args.width))
			putchr(' ');
		if (!s)
			while (6 + i++ < args.width)
				putchr(' ');
		i += putstr(s, args.prec);
		return (i - 1);
	}
}

int	printptr(void *ptr, t_args args)
{
	int					i;

	i = 0;
	if (args.minus)
	{
		i = putptr(ptr);
		while (i++ < args.width)
			putchr(' ');
		return (i - 1);
	}
	else
	{
		while (ft_digits_of_hex((unsigned long long)ptr) + i++ < args.width)
			putchr(' ');
		i += putptr(ptr);
		return (i - 1);
	}
}

int	printhex(unsigned long long a, char begin, t_args args)
{
	int					i;

	i = ((args.tag && a > 0) * 2);
	if (args.minus)
	{	
		if (args.tag && a > 0 && begin == 'a')
			putstr("0x", 2);
		if (args.tag && a > 0 && begin == 'A')
			putstr("0X", 2);
		i += puthex(a, begin, args.prec);
		while (i++ < args.width)
			putchr(' ');
		return (i - 1);
	}
	else
	{
		while (i++ + ft_digits_of_hex(a) < args.width)
			putchr(args.zero);
		if (args.tag && a > 0 && begin == 'a')
			putstr("0x", 2);
		if (args.tag && a > 0 && begin == 'A')
			putstr("0X", 2);
		i += puthex(a, begin, args.prec);
		return (i - 1);
	}
}
