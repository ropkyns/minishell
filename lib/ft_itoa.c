/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:03:12 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/22 11:48:13 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len(long nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len = 1;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static void	ft_fill(char *s, long nb, int *i)
{
	if (nb / 10 != 0)
		ft_fill(s, nb / 10, i);
	s[*i] = '0' + (nb % 10);
	(*i)++;
}

char	*ft_itoa(int n)
{
	int		i;
	long	nbr;
	char	*res;
	int		len;

	nbr = n;
	len = ft_count_len(nbr);
	res = malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		res[i] = '-';
		nbr = -nbr;
		i++;
	}
	ft_fill(res, nbr, &i);
	res[i] = '\0';
	return (res);
}
