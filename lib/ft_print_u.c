/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:51:04 by mjameau           #+#    #+#             */
/*   Updated: 2024/06/18 11:19:33 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_u_digits(unsigned int n)
{
	if (n > 9)
		ft_print_u(n / 10);
	if (n <= 9)
	{
		ft_putchar_fd(n + 48, 1);
		return ;
	}
	ft_putchar_fd((n % 10) + 48, 1);
}

int	ft_print_u(unsigned int n)
{
	unsigned int	i;

	i = 1;
	print_u_digits(n);
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}
