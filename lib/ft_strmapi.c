/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:10:38 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/28 18:01:53 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*scpy;
	size_t			len;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	scpy = (char *)malloc(sizeof(char) * len + 1);
	if (scpy == NULL)
		return (NULL);
	i = 0;
	while (len > i)
	{
		scpy[i] = f(i, s[i]);
		i++;
	}
	scpy[len] = '\0';
	return (scpy);
}
