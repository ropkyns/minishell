/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:00:16 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/01 12:50:18 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* On free tout les tokens, mais vu que c une liste circulaire
bah c'est chiant (mais c'est aussi ma faute)
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
