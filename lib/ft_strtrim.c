/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:00:32 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/28 18:00:10 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*tab;

	i = 0;
	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[start] && ft_is_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_set(s1[end - 1], set))
		end--;
	tab = malloc(sizeof(char) * (end - start + 1));
	if (tab == NULL)
		return (NULL);
	while (start < end)
		tab[i++] = s1[start++];
	tab[i] = '\0';
	return (tab);
}
