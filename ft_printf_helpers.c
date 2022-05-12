/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:17:33 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/12 11:32:25 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	puthex(unsigned long long a, char begin, int precision, int zerox)
{
	unsigned int	i;

	i = 0;
	if (!precision && a == 0)
		return (0);
	if (zerox)
		i += putchr('0');
	if (zerox)
		i += putchr(begin + 23);
	while (precision-- > ft_digits_of_hex(a) + (zerox * 2))
		i += putchr('0');
	if (a > 1 && a >> 4 > 0)
		i += puthex(a >> 4, begin, 0, 0);
	return (i + putchr((a & 0b1111) + ((a & 0b1111) < 10) * 48
			+ ((a & 0b1111) > 9) * (begin - 10)));
}

int	putstr(char *s, int precision)
{
	int	i;

	i = 0;
	if (!s)
		return (putstr("(null)", precision));
	while (s[i] && (precision == -1 || i < precision))
		write(1, s + i++, 1);
	return (i);
}

int	putchr(char c)
{
	write(1, &c, 1);
	return (1);
}

int	putnbr(long long nb, int precision, int sign, int space)
{
	int	i;
	int	v;

	v = 0;
	i = nb < 0;
	if (nb < 0)
		putchr('-');
	if (nb >= 0 && sign)
		i += putchr('+');
	if (nb >= 0 && !sign && space)
		i += putchr(' ');
	if (precision && precision > ft_digits_of_int(nb))
		while (precision > ft_digits_of_int(nb) + v++)
			i += putchr('0');
	if (!precision && nb == 0)
		return (0);
	if (nb < 0)
		nb *= -1;
	if (nb / 10 > 0)
		i += putnbr(nb / 10, -1, 0, 0);
	return (putchr(nb % 10 + '0') + i);
}
