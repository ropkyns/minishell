/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:15 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/08 09:28:47 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* PENSER A INITIALISER DANS LA FONCTION INIT GLOBAL
 */

static t_cmd	*find_last_node_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

static void	add_node_cmd(t_cmd **cmd, char *value)
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
		last_node = find_last_node_cmd(*cmd);
		node->prev = last_node;
		last_node->next = node;
	}
}
/* CHANGER LA MANIERE DE CREER LES MAILLONS (LE FAIRE QUAND Y A UN PIPE) */

void	init_cmd(t_cmd **cmd, t_structok **tok_list)
{
	t_structok	*tmp;
	t_cmd		*last;

	fflush(stdout);
	tmp = *(tok_list);
	while (tmp->next != (*tok_list))
	{
		fflush(stdout);
		add_node_cmd(cmd, NULL);
		fflush(stdout);
		last = find_last_node_cmd(*cmd);
		if (tmp->type == CMD)
			last->cmd = tmp->value;
		else if (tmp->type == INPUT)
			last->infile = open(tmp->next->value, O_CREAT, S_IRWXU);
		else if (tmp->type == OUTPUT)
			last->outfile = open(tmp->next->value, O_CREAT, S_IRWXU);
		else if (tmp->type == PIPE)
			add_node_cmd(cmd, NULL);
		tmp = tmp->next;
	}
}
