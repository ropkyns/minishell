/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:00:16 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/23 16:01:08 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
