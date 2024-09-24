/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:15 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/24 17:57:42 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* PENSER A INITIALISER DANS LA FONCTION INIT GLOBAL
 */

t_cmd	*find_last_node_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	add_node_cmd(t_cmd **cmd, char *value)
{
	t_cmd	*node;
	t_cmd	*last_node;

	if (cmd == NULL)
		return ;
	node = malloc(sizeof(t_cmd));
	if (!node)
		return ;
	node->next = NULL;
	node->cmd = value;
	if (*cmd == NULL)
	{
		node->prev = NULL;
		*cmd = node;
	}
	else
	{
		last_node = find_last_node(*cmd);
		node->prev = last_node;
		last_node->next = node;
	}
}
/* CHANGER LA MANIERE DE CREER LES MAILLONS (LE FAIRE QUAND Y A UN PIPE) */

void	init_cmd(t_cmd **cmd, t_structok **tok_list)
{
	t_structok	*tmp;
	t_cmd		*last;

	tmp = *(tok_list);
	while (tmp->next != (*tok_list))
	{
		last = find_last_node_cmd(cmd);
		if (tmp->type == CMD)
			add_node_cmd(cmd, (*tok_list)->value);
		else if (tmp->type == INPUT)
			last->infile = open(tmp->next->value, O_CREAT);
		else if (tmp->type == OUTPUT)
			last->outfile = open(tmp->next->value, O_CREAT);
		tmp = tmp->next;
	}
}
