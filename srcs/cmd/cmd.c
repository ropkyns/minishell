/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:15 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/23 15:31:29 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_node_cmd(t_cmd **cmd, char *value)
{
	t_cmd	*node;
	t_cmd	*last_node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return ;
	node->next = NULL;
	node->cmd = value;
	node->cmd_args = NULL;
	node->infile = -1;
	node->outfile = -1;
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

void	process_cmd_token(t_cmd **cmd, t_structok *tmp, t_global *glob,
		t_structok *tok_list)
{
	t_cmd	*last;

	last = find_last_node_cmd(*cmd);
	if (last->cmd == NULL)
	{
		last->cmd = ft_strdup(tmp->value);
		last->cmd_args = args_tab(tmp, glob, tok_list);
	}
	else
	{
		add_node_cmd(cmd, NULL);
		last = find_last_node_cmd(*cmd);
		last->cmd = ft_strdup(tmp->value);
		last->cmd_args = args_tab(tmp, glob, tok_list);
	}
}

void	init_cmd(t_cmd **cmd, t_structok **tok_list, t_global *glob)
{
	t_structok	*tmp;
	t_structok	*start;
	t_cmd		*last;

	tmp = *tok_list;
	if (!tmp)
		return ;
	start = tmp;
	add_node_cmd(cmd, NULL);
	last = find_last_node_cmd(*cmd);
	while (1)
	{
		if (tmp->type == CMD)
			process_cmd_token(cmd, tmp, glob, *tok_list);
		else if (tmp->type == INPUT || tmp->type == OUTPUT)
			handle_input_output(last, tmp, glob);
		else if (tmp->type == PIPE)
			add_node_cmd(cmd, NULL);
		tmp = tmp->next;
		if (tmp == start)
			break ;
	}
}
