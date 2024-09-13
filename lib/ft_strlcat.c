/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:00:29 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/25 15:54:30 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;

	lensrc = ft_strlen(src);
	if (siz == 0)
		return (lensrc);
	lendst = ft_strlen(dst);
	i = 0;
	if (siz <= lendst)
		return (lensrc + siz);
	while (src[i] && i < siz - lendst - 1)
	{
		dst[lendst + i] = src[i];
		i++;
	}
	if (siz > lendst)
		dst[lendst + i] = '\0';
	return (lendst + lensrc);
}
