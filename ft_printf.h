/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:16:10 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/04 11:00:52 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_printf(const char *str, ...);
int	putstr(char *s);
int	putchr(char c);
int	putptr(void *ptr);
int	puthex(unsigned long long a, char begin);
int	putnbr(long long nb, int precision);

int	printnbr(long long nb, long args);
int	printchar(char c, long args);
int	printstr(char *s, long args);
int	printptr(void *ptr, long args);
int	printhex(unsigned long long a, char begin, long args);

#endif