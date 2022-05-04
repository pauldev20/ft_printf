/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:17:33 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/04 17:30:01 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

int	puthex(unsigned long long a, char begin, int precision)
{
	unsigned int	i;

	i = 0;
	while (precision-- > ft_digits_of_hex(a))
		i += putchr('0');
	if (a > 1 && a >> 4 > 0)
		i += puthex(a >> 4, begin, precision);
	return (i + putchr((a & 0b1111) + ((a & 0b1111) < 10) * 48
			+ ((a & 0b1111) > 9) * (begin - 10)));
}

int	putptr(void *ptr)
{
	putstr("0x", 2);
	return (puthex((unsigned long long)ptr, 'a', -1) + 2);
}

int	putstr(char *s, int precision)
{
	int	i;

	i = 0;
	if (!s)
		return (putstr("(null)", 7));
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
	{
		while (precision > ft_digits_of_int(nb) + v++)
			i += putchr('0');
	}
	if (nb < 0)
		nb *= -1;
	if (nb / 10 > 0)
		i += putnbr(nb / 10, 0, 0, 0);
	return (putchr(nb % 10 + '0') + i);
}