/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:23:36 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/18 15:29:31 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Check si whitespace ou space
 */
bool	is_space(char c)
{
	if (c && (c >= 9 && c <= 13) || (c == ' '))
		return (true);
	return (false);
}

/*
 * Check si caractere special (operateur), on return le enum
 */
int	is_special(char *token)
{
	if (token && *token && ft_strlen(token) >= 2)
	{
		if (!ft_strncmp(token, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmp(token, ">>", 2))
			return (APPEND);
	}
	if (token && *token && ft_strlen(token) >= 1)
	{
		if (!ft_strncmp(token, ">", 1))
			return (OUTPUT);
		if (!ft_strncmp(token, "<", 1))
			return (INPUT);
		if (!ft_strncmp(token, "|", 1))
			return (PIPE);
	}
	return (0);
}
