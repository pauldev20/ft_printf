/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:52:03 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/05 12:43:34 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int	i;

	i = 0;
	printf("  %d\n", printf("%20x", 3));
	printf("  %d\n", ft_printf("%20x", 3));
	return (0);
}
