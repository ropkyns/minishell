/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:25:00 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/28 18:07:41 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	i = -1;
	slen = ft_strlen(s);
	if (start >= slen)
	{
		str = ft_strdup("");
		if (str == NULL)
			return (NULL);
		return (str);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc(len + 1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (++i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
