/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:00:05 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/22 12:20:40 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	c2;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *)s;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (s2[i] == c2)
			return ((void *)&s[i]);
		i++;
	}
	return (NULL);
}
