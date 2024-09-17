/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:05:01 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/17 15:50:09 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_redir(char *lexer_token)
{
	if (ft_strlen(lexer_token) == 2)
	{
		if (ft_strstr(lexer_token, "<<") || ft_strstr(lexer_token, ">>"))
			return (true);
	}
	if (ft_strlen(lexer_token) == 1)
	{
		if (ft_strstr(lexer_token, '<') || ft_strstr(lexer_token, '>'))
			return (true);
	}
	return (false);
}

static bool	is_pipe(char *curr, char *next)
{
	if (ft_strlen(curr) == 1 && ft_strchr(curr, '|'))
	{
		if (next == NULL)
			return (false);
		if (ft_strlen(next) == 2)
		{
			if (ft_strstr(next, "&&") || ft_strstr(next, "||"))
				return (false);
		}
	}
	return (true);
}

static bool	is_quote(char *lexer_token)
{
	if (ft_strchr(lexer_token, '\'') || ft_strchr(lexer_token, '\"'))
		return (true);
	return (false);
}

static bool	is_special(char *lexer_token, int flag)
{
	if (ft_strlen(lexer_token) == 2 && flag == 0)
		if ((ft_strchr(lexer_token, '<') && !ft_strstr(lexer_token, "<<")
				|| (ft_strchr(lexer_token, '>')) && !ft_strstr(lexer_token,
					">>") || (ft_strchr(lexer_token, '|'))
				&& !ft_strstr(lexer_token, "||")))
			return (true);
	if (ft_strlen(lexer_token) == 2 && flag == 0)
		if (ft_strstr(lexer_token, "<<") || ft_strstr(lexer_token, ">>"))
			return (true);
	if (ft_strlen(lexer_token) == 2 && flag == 3)
		if (ft_strstr(lexer_token, "&&") || ft_strstr(lexer_token, "||"))
			return (true);
}

static bool	special_is_correct(char *lexer_token)
{
	if (lexer_token[0] == '(' && ft_strchr(lexer_token, ')'))
		return (true);
	if (ft_strlen(lexer_token) != 2)
	{
		if (ft_strstr(lexer_token, "&&") || ft_strstr(lexer_token, "||")
			|| ft_strstr(lexer_token, "<<") || ft_strstr(lexer_token, ">>"))
			return (false);
		if (ft_strchr(lexer_token, '&'))
			return (false);
	}
	if (ft_strlen(lexer_token) != 1)
	{
		if ((ft_strchr(lexer_token, '<') && !ft_strstr(lexer_token, "<<"))
			|| (ft_strchr(lexer_token, '>') && !ft_strstr(lexer_token, ">>"))
			|| (ft_strchr(lexer_token, '|') && !ft_strstr(lexer_token, "||")))
			return (false);
	}
	return (true);
}

bool	syntax_is_correct(char *lexer_tokens[])
{
	int	i;

	i = 0;
	while (lexer_tokens[i])
	{
		if (!is_quote(lexer_tokens[i]))
		{
			if (!special_is_correct(lexer_tokens[i]))
				return (false);
			if (!is_pipe(lexer_tokens[i], lexer_tokens[i + 1]))
				return (false);
			if (ft_strchr(lexer_tokens[i], '(') && ft_strchr(lexer_tokens[i],
					')'))
				if (i != 0 && is_special(lexer_tokens[i - 1], 0))
					return (false);
		}
	}
}
