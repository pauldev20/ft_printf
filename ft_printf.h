/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:16:10 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/20 13:45:43 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "./libft/libft.h"

typedef struct s_args {
	int	minus;
	int	zero;
	int	prec;
	int	width;
	int	space;
	int	plus;
	int	tag;
}	t_args;

int	ft_printf(const char *str, ...);
int	putstr(char *s);
int	putchr(char c);
int	puthex(unsigned long long a, char begin, int zerox);
int	putnbr(long long nb);

#endif