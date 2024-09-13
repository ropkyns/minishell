/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:14:32 by mjameau           #+#    #+#             */
/*   Updated: 2024/05/28 18:00:53 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	safe_malloc(char **token_v, int position, size_t buffer)
{
	int	i;

	i = 0;
	token_v[position] = malloc(buffer);
	if (token_v[position] == NULL)
	{
		while (i < position)
			free(token_v[i++]);
		free(token_v);
		return (1);
	}
	return (0);
}

static int	fill(char **token_v, char const *s, char delimeter)
{
	int		i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (safe_malloc(token_v, i, len + 1))
				return (1);
			ft_strlcpy(token_v[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

static size_t	count_tokens(char const *s, char delimeter)
{
	size_t	tokens;
	int		i;

	tokens = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != delimeter) && ((s[i + 1] == delimeter) || (s[i + 1] == 0)))
			++tokens;
		i++;
	}
	return (tokens);
}

char	**ft_split(char const *s, char c)
{
	size_t	tokens;
	char	**token_v;

	if (s == NULL)
		return (NULL);
	tokens = count_tokens(s, c);
	token_v = malloc((tokens + 1) * sizeof(char *));
	if (token_v == NULL)
		return (NULL);
	token_v[tokens] = NULL;
	if (fill(token_v, s, c))
		return (NULL);
	return (token_v);
}
