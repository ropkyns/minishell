/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:51:15 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/27 14:55:09 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		*mem;
	size_t	totsize;

	mem = NULL;
	totsize = nmemb * size;
	if ((totsize < size || totsize < nmemb) && totsize > 0)
		return (NULL);
	mem = malloc(totsize);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, 0, totsize);
	return (mem);
}
