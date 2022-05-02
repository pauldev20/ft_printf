/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:32:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/02 17:45:35 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft/libft.h"

int	putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (putstr("(null)"));
	while (s[i])
		write(1, s + i++, 1);
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	puthex(unsigned long long a, char begin, long args)
{
	unsigned int	i;

	i = 0;
	if ((args & 0b1111) == 1)
		putstr("0x");
	if (a > 1 && a >> 4 > 0)
		i = puthex(a >> 4, begin, args >> 4 << 4);
	return (i + ft_putchar((a & 0b1111) + ((a & 0b1111) < 10) * 48
			+ ((a & 0b1111) > 9) * (begin - 10)));
}

int	putptr(void *ptr)
{
	putstr("0x");
	return (puthex((unsigned long long)ptr, 'a', 0) + 2);
}

int	putnbr(long long nb, long args)
{
	int		digits;
	int		i;
	int		v;
	int		sign;
	long	num;

	i = 0;
	sign = 0;
	digits = ft_digits_of_int(nb);
	while ((args >> 12 & 0b1111111111111111) > 0)
	{
		if (((args >> 12 & 0b1111111111111111) - digits) > 0)
		{
			if ((args >> 44 & 0b1111) > 0)
				ft_putchar('0');
			else
				ft_putchar(' ');
		}
		args -= 1L << 12;
	}
	if ((args >> 8 & 0b1111) == 1 && nb > 0)
		ft_putchar('+');
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
		sign = 1;
	}
	while (i < digits)
	{
		num = nb;
		v = digits - 1 - i++;
		while (v--)
			num /= 10;
		ft_putchar((num % 10) + '0');
	}
	return (digits + sign);
}
