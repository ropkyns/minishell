/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:54:48 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/20 13:55:11 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*result;

	len = 0;
	while (s[len] && len < n)
		len++;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s, len);
	result[len] = '\0';
	return (result);
}
