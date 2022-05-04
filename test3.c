/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:22:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/03 22:16:33 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"

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

// 0000 0000 prec prec prec prec - 0? 0? width width width width + space 0x
long	parse_args(char **token)
{
	long	rtn;

	rtn = 0;
	while (!is_token(**token))
	{
		if (**token == '#')
			rtn += 0b0001 << 0;
		if (**token == ' ')
			rtn += 0b0001 << 4;
		if (**token == '+')
			rtn += 0b0001 << 8;
		if (**token == '0' && !(rtn >> 44 & 0b11111111))
			rtn += (long)'0' << 44;
		else if (!(rtn >> 44 & 0b11111111))
			rtn += (long)' ' << 44;
		if (**token == '-')
			rtn += (long)0b0001 << 52;
		if (**token == '.')
		{
			rtn += (long)ft_atoi(*token + 1) << 56;
			*token += ft_digits_of_int(ft_atoi(*token + 1));
		}
		else if (ft_isdigit(**token) && (**token != '0'))
		{
			rtn += (long)ft_atoi(*token) << 12;
			*token += ft_digits_of_int(ft_atoi(*token)) - 1;
		}
		(*token)++;
	}
	return (rtn);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	putnbr(long long nb, int precision)
{
	int	i;
	int v;

	v = 0;
	i = nb < 0;
	if (nb < 0)
		ft_putchar('-');
	if (precision && precision > ft_digits_of_int(nb))
	{
		while (precision > ft_digits_of_int(nb) + v++)
			i += ft_putchar('0');
	}
	if (nb < 0)
		nb *= -1;
	if (nb / 10 > 0)
		i += putnbr(nb / 10, 0);
	return (ft_putchar(nb % 10 + '0') + i);
}

int	printnbr(long long nb, long args)
{
	int	i;
	int	v;

	v = 0;
	if (args >> 52 & 0b1111)
	{
		i = putnbr(nb, args >> 56 & 0b1111111111111111);
		while (i++ < (args >> 12 & 0b1111111111111111))
			ft_putchar(args >> 44 & 0b11111111);
		return (i - 1);
	}
	else
	{
		i = 0;
		if ((args >> 44 & 0b11111111) == '0')
			return (putnbr(nb, (args >> 12 & 0b1111111111111111) - 1));
		while (ft_digits_of_int(nb) + (nb < 0) + ((args >> 56 & 0b1111111111111111)
				- ft_digits_of_int(nb)) + i++ < (args >> 12 & 0b1111111111111111))
			ft_putchar(' ');
		i += putnbr(nb, args >> 56 & 0b1111111111111111);
		return (i - 1);
	}
}

int	main(void)
{
	char *test = "-8";
	long a = parse_args(&test);
	printf("   %d\n", printnbr(-10, a));
	printf("   %d\n", printf("%-8d", -10));
	return (0);
}
