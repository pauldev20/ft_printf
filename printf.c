/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:19:52 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/25 17:00:33 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "./libft/libft.h"
#include <stdarg.h>

#include <stdio.h>

void	parse_token(char *tokenstr)
{
	printf("token: %s\n", tokenstr);
}

int	ft_printf(const char *str, ...)
{
	char	**rtn;
	int		i;
	va_list	vl;

	i = 0;
	rtn = ft_split(str, '%');
	while (*str)
	{
		if (*str == '%')
			parse_token(rtn[i++]);
		ft_putchar_fd(*(str++), 1);
	}
	return (0);
}
