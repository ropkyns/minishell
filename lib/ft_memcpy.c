/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:42:06 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/22 16:23:26 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*dst;
	const char		*sourc;

	if (dest == NULL && src == NULL)
		return (NULL);
	dst = dest;
	sourc = src;
	i = 0;
	while (i < n)
	{
		dst[i] = sourc[i];
		i++;
	}
	return (dest);
}
