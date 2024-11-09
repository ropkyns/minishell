/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:11:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/09 13:57:55 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Trouve la derniere node dans la liste des cmd
 */
t_cmd	*find_last_node_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

/*
 * Comptre le nombre d'arguments dans la list des tokens
 */
static int	count_args(t_structok *toklist, t_structok *head)
{
	int			count;
	t_structok	*tmp;

	count = 0;
	tmp = toklist;
	while (tmp->next != head && (tmp->next->type == ARG
			|| tmp->next->type == CMD))
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

/*
* Rempli le tableau de char **ret avec les value des tokens.
on copie cmd direct, ensuite on avance et on ajoute les ARG et CMD et on les
ajoute au tableau (en gros on prend CMD et ARG et on les fout dans un tab)
*/
static void	fill_args_array(char **ret, t_structok *toklist, t_global *glob,
		t_structok *head)
{
	int	i;

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
}

/*
* On compte le nb d'args pour pouvoir malloc notre tableau de
char * + 2 parce que '\0' et la cmd
ensuite on appelle fill_args pour qu'il remplisse le tableau
*/
char	**args_tab(t_structok *toklist, t_global *glob, t_structok *head)
{
	int		arg_count;
	char	**ret;

	arg_count = count_args(toklist, head);
	ret = malloc(sizeof(char *) * (arg_count + 2));
	if (!ret)
		error_exit("Allocation failed", glob);
	fill_args_array(ret, toklist, glob, head);
	return (ret);
}
