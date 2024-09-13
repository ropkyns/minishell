/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:41:36 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/21 12:24:06 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			c2;

	i = 0;
	c2 = (char)c;
	while (s[i])
	{
		if (s[i] == c2)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c2)
		return ((char *)&s[i]);
	return (NULL);
}
