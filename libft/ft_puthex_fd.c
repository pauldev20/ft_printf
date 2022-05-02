/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:17:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/26 17:05:30 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	put_hex_char(long nb, char charbegin, int fd)
{
	if (nb < 10)
		ft_putchar_fd(nb + '0', fd);
	else
		ft_putchar_fd(nb - 10 + charbegin, fd);
	return (1);
}

int	ft_puthex_fd(unsigned long long nb, int fd, char charbegin)
{
	int					digits;
	int					i;
	int					v;
	int					rtn;
	unsigned long long	num;

	i = 0;
	rtn = 0;
	if (nb == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	digits = ft_digits_of_int(nb);
	while (i < digits)
	{
		num = nb;
		v = digits - 1 - i++;
		while (v--)
			num /= 16;
		if ((!(i - 1) && num > 0) || num > 0)
			rtn += put_hex_char(num % 16, charbegin, fd);
	}
	return (rtn);
}
