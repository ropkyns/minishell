/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:45:56 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/21 14:46:27 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*pos;
	char	c2;

	i = 0;
	pos = NULL;
	c2 = (char)c;
	while (s[i])
	{
		if (s[i] == c2)
			pos = (char *)&s[i];
		i++;
	}
	if (s[i] == c2)
		pos = (char *)&s[i];
	return (pos);
}
