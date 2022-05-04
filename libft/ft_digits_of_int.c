/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits_of_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:32:14 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/03 15:11:46 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_digits_of_int(long long n)
{
	int		digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}
