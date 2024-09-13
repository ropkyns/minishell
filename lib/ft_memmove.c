/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:45:54 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/22 18:33:05 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*dst;
	char			*sourc;

	if (dest == NULL && src == NULL)
		return (NULL);
	dst = (char *)dest;
	sourc = (char *)src;
	i = 0;
	if (sourc < dst)
	{
		while (n-- > 0)
			dst[n] = sourc[n];
	}
	else
	{
		while (i < n)
		{
			dst[i] = sourc[i];
			i++;
		}
	}
	return (dest);
}
