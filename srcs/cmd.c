/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:15 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/10 12:39:22 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* PENSER A INITIALISER DANS LA FONCTION INIT GLOBAL
 */

static char	**args_tab(t_structok **toklist, t_global *glob, t_structok *head)
{
	int			i;
	char		**ret;
	t_structok	*tmp;

	i = 0;
	tmp = (*toklist);
	while ((tmp->next->type == ARG || tmp->next->type == CMD) 
		&& tmp->next != head)
	{
		i++;
		tmp = tmp->next;
	}
	ret = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (((*toklist)->next->type == ARG || (*toklist)->next->type == CMD) 
		&& (*toklist)->next != head)
	{
		ret[i] = ft_strdup((*toklist)->value);
		if (!ret[i])
			error_exit("Allocation failed", glob);
		i++;
		(*toklist) = (*toklist)->next;
	}
	ret[i] = NULL;
	return (ret);
}

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

static void	handle_input_output(t_cmd *last, t_structok *toklist,
			t_global *glob)
{
	if (toklist->type == INPUT)
	{
		last->infile = open(toklist->next->value, 0);
		if (last->infile == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(toklist->next->value, 2);
			ft_putstr_fd(": No such file or directory", 2);
			error_exit(NULL, glob);
		}
	}
	else if (toklist->type == OUTPUT)
			last->outfile = open(toklist->next->value, O_CREAT, S_IRWXU);
}
//FAIRE UN BON PRINT : "BASH:[NOM DU FICHIER]:NO SUCH FILE OR DIRECTORY"

/* CHANGER LA MANIERE DE CREER LES MAILLONS (LE FAIRE QUAND Y A UN PIPE) */
void	init_cmd(t_cmd **cmd, t_structok **tok_list, t_global *glob)
{
	t_structok	*tmp;
	t_cmd		*last;

	tmp = *(tok_list);
	while (tmp->next != (*tok_list))
	{
		add_node_cmd(cmd, NULL);
		last = find_last_node_cmd(*cmd);
		if (tmp->type == CMD)
		{
			last->cmd = tmp->value;
			last->cmd_args = args_tab(&tmp, glob, (*tok_list));
			while (tmp->type == ARG)
				tmp = tmp->next;
		}
		else if (tmp->type == INPUT || tmp->type == OUTPUT)
			handle_input_output(last, tmp, glob);
		else if (tmp->type == PIPE)
			add_node_cmd(cmd, NULL);
		tmp = tmp->next;
	}
}
