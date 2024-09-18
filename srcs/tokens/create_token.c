/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:29:07 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/18 16:08:43 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * On malloc et initialise la nouvelle node de la liste chainee
 */
int	new_token(t_structok **new, char *s, t_token type)
{
	if (!s)
		return (0);
	*new = malloc(sizeof(t_structok));
	if (!new)
	{
		free(s);
		return (0);
	}
	(*new)->value = s;
	(*new)->type = type;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

/*
* On ajoute le nouveau token en appelant la fonction new_token
on refait aussi les liens de la nouvelle node (on l'ajoute a l'indice
precedant l'indice pointe par *token_list) ainsi que les liens de token_list
vu qu'on la decale.
*/
int	add_token(t_structok **token_list, char *s, int type)
{
	t_structok	*new;

	if (!new_token(&new, s, type))
		return (0);
	new->prev = (*token_list)->prev;
	new->next = (*token_list);
	(*token_list)->prev->next = new;
	(*token_list)->next = new;
	return (1);
}

/*
 * TODO
 */
bool	add_operator_token(t_structok **head, char **command)
{
	int checker;

	checker = is_special(*command);
	// en fonction de ce que nous retourne la fonction is_special
	// faire un strdup de l'operateur, ex ;
	// if (is_special(checker) == INPUT)
	// 		add_token(*command, ft_strdup('<'), INPUT)
}