/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:32:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/04 11:44:19 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft/libft.h"
#include "ft_printf.h"

#include <stdio.h>

int	printnbr(long long nb, long args)
{
	int	i;

	if (args >> 52 & 0b1111)
	{
		i = putnbr(nb, args >> 56 & 0b1111111111111111);
		while (i++ < (args >> 12 & 0b1111111111111111))
			putchr(args >> 44 & 0b11111111);
		return (i - 1);
	}
	else
	{
		i = 0;
		if ((args >> 44 & 0b11111111) == '0')
			return (putnbr(nb, (args >> 12 & 0b1111111111111111) - (nb < 0)));
		while (ft_digits_of_int(nb) + (nb < 0) + ((args >> 56 & 0b1111111111111111)
				- ft_digits_of_int(nb)) + i++ < (args >> 12 & 0b1111111111111111))
			putchr(' ');
		i += putnbr(nb, args >> 56 & 0b1111111111111111);
		return (i - 1);
	}
}

int	printchar(char c, long args)
{
	int	i;

	if (args >> 52 & 0b1111)
	{
		i = putchr(c);
		while (i++ < (args >> 12 & 0b1111111111111111))
			putchr(' ');
		return (i - 1);
	}
	else
	{
		i = 0;
		while (1 + i++ < (args >> 12 & 0b1111111111111111))
			putchr(' ');
		i += putchr(c);
		return (i - 1);
	}
}

int	printstr(char *s, long args)
{
	int	i;

	if (args >> 52 & 0b1111)
	{
		if ((args >> 56 & 0b1111111111111111))
			i = write(1, s, (args >> 56 & 0b1111111111111111));
		else
			i = write(1, s, ft_strlen(s));
		while (i++ < (args >> 12 & 0b1111111111111111))
			putchr(' ');
		return (i - 1);
	}
	else
	{
		i = 0;
		while (ft_strlen(s) + i++ < (args >> 12 & 0b1111111111111111))
			putchr(' ');
		if ((args >> 56 & 0b1111111111111111) && ft_strlen(s) > 0)
			i += write(1, s, (args >> 56 & 0b1111111111111111));
		else if (ft_strlen(s) > 0)
			i += write(1, s, ft_strlen(s));
		return (i - 1);
	}
}

int	printptr(void *ptr, long args)
{
	int					i;
	unsigned long long	v;

	if (args >> 52 & 0b1111)
	{
		i = putptr(ptr);
		while (i++ < (args >> 12 & 0b1111111111111111))
			putchr(' ');
		return (i - 1);
	}
	else
	{
		i = 2;
		v = (unsigned long long)ptr;
		while (v > 0 && i++)
			v /= 16;
		while (i++ < (args >> 12 & 0b1111111111111111))
			putchr(' ');
		putptr(ptr);
		return (i - 1);
	}
}

int	printhex(unsigned long long a, char begin, long args)
{
	int					i;
	unsigned long long	v;

	i = ((args & 0b1111) * 2);
	if (args >> 52 & 0b1111)
	{		
		if ((args & 0b1111) == 1)
			putstr("0x");
		i += puthex(a, begin);
		while (i++ < (args >> 12 & 0b1111111111111111))
			putchr(' ');
		return (i - 1);
	}
	else
	{
		i += 1 + (a == 0);
		v = a;
		while (v > 0 && i++)
			v /= 16;
		i--;
		while (i++ < (args >> 12 & 0b1111111111111111))
			putchr(args >> 44 & 0b11111111);
		if ((args & 0b1111) == 1)
			i += putstr("0x");
		puthex(a, begin);
		return (i - 1);
	}
}
