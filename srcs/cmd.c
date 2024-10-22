/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:15 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/22 19:40:49 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* PENSER A INITIALISER DANS LA FONCTION INIT GLOBAL
 */

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

/* PENSER A INITIALISER DANS LA FONCTION INIT GLOBAL
 */
static char	**args_tab(t_structok *toklist, t_global *glob, t_structok *head)
{
	int			i;
	char		**ret;
	t_structok	*tmp;

	i = 0;
	tmp = toklist;
	while (tmp->next != head && (tmp->next->type == ARG
			|| tmp->next->type == CMD))
	{
		i++;
		tmp = tmp->next;
	}
	ret = malloc(sizeof(char *) * (i + 2));
	i = 0;
	if (toklist->type == CMD)
	{
		ret[i] = ft_strdup(toklist->value);
		if (!ret[i])
			error_exit("Allocation failed", glob);
		i++;
	}
	while (toklist->next != head && (toklist->next->type == ARG
			|| toklist->next->type == CMD))
	{
		if (toklist->next->value)
		{
			ret[i] = ft_strdup(toklist->next->value);
			if (!ret[i])
				error_exit("Allocation failed", glob);
		}
		else
			ret[i] = NULL;
		i++;
		toklist = toklist->next;
	}
	ret[i] = NULL;
	return (ret);
}

static t_cmd	*find_last_node_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

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

// void	init_cmd(t_cmd **cmd, t_structok **tok_list, t_global *glob)
// {
// 	t_structok	*tmp;
// 	t_cmd	*last;

// 	tmp = *tok_list;
// 	if (!tmp)
// 		return ;
// 	add_node_cmd(cmd, NULL);
// 	while (tmp->next != (*tok_list))
// 	{
// 		last = find_last_node_cmd(*cmd);
// 		if (tmp->type == CMD)
// 		{
// 			last->cmd = ft_strdup(tmp->value);
// 			last->cmd_args = args_tab(tmp, glob, *tok_list);
// 		}
// 		else if (tmp->type == INPUT || tmp->type == OUTPUT)
// 		{
// 			handle_input_output(last, tmp, glob);
// 		}
// 		else if (tmp->type == PIPE)
// 		{
// 			add_node_cmd(cmd, NULL);
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	init_cmd(t_cmd **cmd, t_structok **tok_list, t_global *glob)
{
	t_structok *tmp;
	t_cmd *last;
	t_structok *start;

	tmp = *tok_list;
	if (!tmp)
		return ;
	start = tmp; // Garder une référence au début de la liste
	// Initialiser le premier noeud de commande
	add_node_cmd(cmd, NULL);
	last = find_last_node_cmd(*cmd);
	while (1) // Boucle infinie
	{
		// Si le token est une commande
		if (tmp->type == CMD)
		{
			if (last->cmd == NULL) // Si le dernier n'a pas encore de commande
			{
				last->cmd = ft_strdup(tmp->value);
				last->cmd_args = args_tab(tmp, glob, *tok_list);
			}
			else
			{
				// Ajouter un nouveau noeud pour la commande suivante (après un pipe)
				add_node_cmd(cmd, NULL);
				last = find_last_node_cmd(*cmd);
				last->cmd = ft_strdup(tmp->value);
				last->cmd_args = args_tab(tmp, glob, *tok_list);
			}
			// Debug output
			printf("Command: %s\n", last->cmd);
			if (last->cmd_args)
			{
				printf("Command args: ");
				for (int i = 0; last->cmd_args[i] != NULL; i++)
				{
					printf("%s ", last->cmd_args[i]);
				}
				printf("\n");
			}
		}
		else if (tmp->type == INPUT || tmp->type == OUTPUT)
		{
			// Gérer les redirections si besoin
			handle_input_output(last, tmp, glob);
		}
		else if (tmp->type == PIPE)
		{
			// Ajouter un nouveau noeud de commande pour chaque pipe
			add_node_cmd(cmd, NULL);
			last = find_last_node_cmd(*cmd);
			// Réinitialiser last au nouveau noeud
		}
		// Passer au token suivant
		tmp = tmp->next;
		// Vérifier si nous avons fait un tour complet de la liste
		if (tmp == start)
			break ; // Sortir de la boucle si on revient au début
	}
}