/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:23:36 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/19 09:25:14 by mjameau          ###   ########.fr       */
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

/*
* On free tout les tokens, on copie le 1er element de la liste dans curr
ensuite on va parcourir tout les tokens dont le ->next ne pointe pas sur le
premier element de la liste. (En gros tous sauf le dernier)
On prend les element dans temp et on free (+ simple pour le premier)
ensuite une fois la boucle finie on free le dernier element.
On free la value (str) d'abord parce que on l'a mit avec strdup
*/
void	free_tok(t_structok **token_list)
{
	t_structok	*curr;
	t_structok	*temp;

	if (!*token_list)
		return ;
	curr = *token_list;
	while (curr->next != *token_list)
	{
		temp = curr;
		curr = curr->next;
		free(temp->value);
		free(temp);
	}
	free(curr->value);
	free(curr);
	*token_list = NULL;
}
