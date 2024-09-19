/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:29:07 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/19 09:35:36 by mjameau          ###   ########.fr       */
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
 * On ajoute un token operateur a la liste chainee avec add_token
 On check si la command a un operateur avec is_special, si oui en fonction
 de ce que la fonction nous retourne on fait un strdup de ce token et on l'ajoute
 avec add_token.
 Ensuite on incremente de la longueur du token pour passer a la suite
 */
bool	add_operator_token(t_structok **head, char **command)
{
	int	checker;

	checker = is_special(*command);
	if (!checker)
		return (false);
	if ((checker == INPUT && !add_token(head, ft_strdup("<"), INPUT))
		|| checker == OUTPUT && !add_token(head, ft_strdup(">"), OUTPUT)
		|| checker == PIPE && !add_token(head, ft_strdup("|"), PIPE)
		|| checker == APPEND && !add_token(head, ft_strdup(">>"), APPEND)
		|| checker == HEREDOC && !add_token(head, ft_strdup("<<"), HEREDOC))
		return (false);
	if (checker == INPUT || checker == OUTPUT || checker == PIPE)
		*command++;
	else if (checker == HEREDOC || checker == APPEND)
		*command += 2;
	return (true);
}

/*
 * TODOoooooOOoo et pas tout doux mdr
 */
bool	do_list_token(t_structok **head, char *command)
{
	int i;
	i = 0;

	*head == NULL;
	while (command[i])
	{
		while (is_space(command[i]))
			i++;
		if (command[i] && !is_special(command[i]) &&
			//faire fonction pour la commande mskine)
		{
			if (*head)
				free_tok(head);
			return (false);
		}
		else if (command[i] && !is_special(command[i])
			&& !add_operator_token(head, command))
		{
			if (*head)
				free_tok(head);
			return (false);
		}
		i++;
	}
	return (true);
}