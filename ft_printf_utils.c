/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:32:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/02 12:37:57 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return putstr("(null)");
	while (s[i])
		write(1, s + i++, 1);
	return (i);
}

int	putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	putptr(void *ptr, int fd)
{
	putstr("0x");
	return (ft_puthex_fd((unsigned long long)ptr, fd, 'a') + 2);
}

int	printhex(long long a, char begin)
{
	unsigned int	i;

	i = 0;
	if (a > 1)
		i = printhex(a >> 4, begin);
	return (i + putchar((a & 0b1111) + ((a & 0b1111) < 10) * 48
			+ ((a & 0b1111) > 9) * (begin - 10)));
}
