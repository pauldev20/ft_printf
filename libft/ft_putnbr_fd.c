/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:39:17 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/26 16:22:24 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long nb, int fd)
{
	int		digits;
	int		i;
	int		v;
	int		neg;
	long	num;

	i = 0;
	neg = 0;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
		neg = 1;
	}
	digits = ft_digits_of_int(nb);
	while (i < digits)
	{
		num = nb;
		v = digits - 1 - i++;
		while (v--)
			num /= 10;
		ft_putchar_fd((num % 10) + '0', fd);
	}
	return (digits + neg);
}
