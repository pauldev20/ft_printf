/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:32:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/20 13:40:31 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	printnbr(long long nb, t_args args)
{
	int	i;

	i = 0;
	if (args.minus)
	{
		i = putnbr(nb, args.prec, args.plus, args.space);
		while (i++ < (args.width))
			putchr(' ');
		return (i - 1);
	}
	if (args.zero && !(args.prec >= 0))
		return (putnbr(nb, args.width - (nb < 0), args.plus, args.space));
	while ((ft_digits_of_int(nb) * !(!args.prec && nb == 0))
		+ (nb < 0) + (args.plus * (nb >= 0))
		+ (args.space * (!args.plus && nb >= 0))
		+ (args.prec - ft_digits_of_int(nb) > 0)
		* (args.prec - ft_digits_of_int(nb)) + i++ < args.width)
		putchr(' ');
	i += putnbr(nb, args.prec, args.plus, args.space);
	return (i - 1);
}

int	printchar(char c, t_args args)
{
	int	i;

	i = 0;
	if (args.minus)
	{
		i = putchr(c);
		while (i++ < args.width)
			putchr(' ');
		return (i - 1);
	}
	while (1 + i++ < args.width)
		putchr(' ');
	i += putchr(c);
	return (i - 1);
}

int	printstr(char *s, t_args args)
{
	int	i;

	i = 0;
	if (args.minus)
	{
		i = putstr(s, args.prec);
		while (i++ < args.width)
			putchr(' ');
		return (i - 1);
	}
	while (s && (((int)ft_strlen(s)
				* (args.prec == -1 || args.prec >= (int)ft_strlen(s)))
			+ (args.prec * (args.prec < (int)ft_strlen(s) && args.prec > 0)))
		+ i++ < args.width)
		putchr(' ');
	while (!s && (((int)ft_strlen("(null)") * (args.prec == -1 || args.prec
					>= (int)ft_strlen("(null)"))) + (args.prec
				* (args.prec < (int)ft_strlen("(null)") && args.prec > 0)))
		+ i++ < args.width)
		putchr(' ');
	i += putstr(s, args.prec);
	return (i - 1);
}

int	printptr(void *ptr, t_args args)
{
	int	i;

	i = 0;
	if (args.minus)
	{
		i += putstr("0x", 2);
		if (args.prec > 0 || ptr != NULL)
			i += puthex((unsigned long long)ptr, 'a', -1, 0);
		while (i++ < args.width)
			putchr(' ');
		return (i - 1);
	}
	while ((ft_digits_of_hex((unsigned long long)ptr)
			* (args.prec > 0 || ptr != NULL)) + 2 + i++ < args.width)
		putchr(' ');
	i += putstr("0x", 2);
	if (args.prec > 0 || ptr != NULL)
		i += puthex((unsigned long long)ptr, 'a', -1, 0);
	return (i - 1);
}

int	printhex(unsigned long long a, char begin, t_args args)
{
	int	i;

	i = 0;
	if (args.minus)
	{
		i = puthex(a, begin, args.prec, args.tag);
		while (i++ < args.width)
			putchr(' ');
		return (i - 1);
	}
	if (args.zero && !(args.prec >= 0))
		return (puthex(a, begin, args.width, args.tag));
	while ((ft_digits_of_hex(a) * !(!args.prec && a == 0))
		+ ((args.tag && a > 0) * 2)
		+ (args.prec - ft_digits_of_hex(a) > 0)
		* (args.prec - ft_digits_of_hex(a)) + i++ < args.width)
		putchr(' ');
	i += puthex(a, begin, args.prec, args.tag && a > 0);
	return (i - 1);
}
