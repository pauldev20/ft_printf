/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:59:35 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/27 21:12:50 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <unistd.h>

// int	printhex(long long a, char begin)
// {
// 	unsigned int	i;

// 	i = 0;
// 	if (a > 1)
// 		i = printhex(a >> 4, begin);
// 	return (i + ft_putchar_fd((a & 0b1111) + ((a & 0b1111) < 10) * 48
// 			+ ((a & 0b1111) > 9) * (begin - 10), 1));
// }

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	printhex(long long a, char *basetext)
{
	unsigned int	i;

	i = 0;
	if (a > 1)
		i = printhex(a / ft_strlen(basetext), basetext);
	
	return (i + ft_putchar_fd(basetext[(a & 0b1111)], 1));
}

void	peinthex(int i)
{
	printf("%c", i + (i < 10) * 48 + (i > 9) * ('A' - 10));
}

int	main(void)
{
	int	i;

	i = 0;
	printf("%p\n", &i);
	printf("0x"); fflush(stdout);
	printf(" %d\n", (printhex(10, "0123456789")));
}
