/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palu <palu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:00:05 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/16 12:57:22 by palu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t	i;

	str = (const unsigned char *)s;
	i = 0;
	while (i < n && str[i] != c)
		i++;
	if (str[i] == c)
	{
		return ((char *)&str[i]);
	}
	return 0;
}
