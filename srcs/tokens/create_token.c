/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:29:07 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/26 12:02:48 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * On malloc et initialise la nouvelle node de la liste chainee
 */
static int	new_token(t_structok **new, char *s, t_token type)
{
	if (!s)
		return (0);
	(*new) = malloc(sizeof(t_structok));
	if (*new == NULL)
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
si c'est la premiere node alors on appelle add_first_token pour
gerer ses liens prev et next correctement,
sinon on gere les liens (c'est une liste circulaire (pour le plus
grand bonheur de mon mate) c'est pour ca que la gestion des chaines
est + chiante hihi)
*/
int	add_token(t_structok **token_list, char *s, int type)
{
	t_structok	*new;

	if (!new_token(&new, s, type))
		return (0);
	if (!(*token_list))
		add_first_token(token_list, new);
	else
	{
		new->prev = (*token_list)->prev;
		new->next = (*token_list);
		(*token_list)->prev->next = new;
		(*token_list)->prev = new;
	}
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
	if (checker == PIPE && !add_token(head, ft_strdup("|"), PIPE))
		return (false);
	else if (checker == INPUT && !add_token(head, ft_strdup("<"), INPUT))
		return (false);
	else if (checker == HEREDOC && !add_token(head, ft_strdup("<<"), HEREDOC))
		return (false);
	else if (checker == OUTPUT && !add_token(head, ft_strdup(">"), OUTPUT))
		return (false);
	else if (checker == APPEND && !add_token(head, ft_strdup(">>"), APPEND))
		return (false);
	if (checker == INPUT || checker == OUTPUT || checker == PIPE)
		(*command)++;
	else if (checker == HEREDOC || checker == APPEND)
		(*command) += 2;
	return (true);
}

/*
 * Fonction pour ajouter les tokens CMD et ARG, on calcule la len
 de la ligne de commande avec len_cmd, on malloc une nouvelle chaine
 sur qui on va copier les tokens, on va ensuite ajouter ces nouveaux tokens
 dans notre liste chainee et definir leurs type CMD et ARG.
 bravo le vo
 */
bool	add_cmd_arg(t_structok **head, char **command)
{
	int		i;
	int		quote;
	char	*str;
	int		len;

	i = 0;
	len = len_cmd(*command, &quote);
	if (((len) - (2 * quote)) < 0)
		return (true);
	str = malloc(sizeof(char) * ((len + 1) - (quote * 2)));
	if (!str)
		return ((false));
	get_words_to_token(*command, len - (2 * quote), str, i);
	if (!add_token(head, str, 0))
		return (false);
	if ((*head)->prev == (*head) || (*head)->prev->prev->type == PIPE)
		(*head)->prev->type = CMD;
	else
		(*head)->prev->type = ARG;
	(*command) += len;
	return (true);
}

/*
 * Ici c'est un peu la fonction qui fait tout,
 on appelle toute les fonctions dans les conditions et
 si l'une d'elle rate on free!
 1->on ignore les whitsepace
 2->on fait les tokens CMD ARG
 3->on fait les tokens << < >> > |
 et bravo
 */
bool	do_list_token(t_structok **head, char *command)
{
	(*head) = NULL;
	while (*command)
	{
		while (is_space(*command))
			command++;
		if (*command && !is_special(command) && !add_cmd_arg(head, &command))
		{
			if (*head)
				free_tok(head);
			return (false);
		}
		else if (*command && is_special(command) && !add_operator_token(head,
				&command))
		{
			if (*head)
				free_tok(head);
			return (false);
		}
	}
	return (true);
}
