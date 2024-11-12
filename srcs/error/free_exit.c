/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:33:24 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/12 11:08:52 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Notre fonction d'exit (car perror ca pue), ici on affiche une str
de notre choix et on free tout
*/
void	error_exit(char *str, t_global *glob)
{
	int	exit_val;

	exit_val = glob->exit_value;
	if (glob->env)
		free_env(glob->env);
	if (glob->path)
		free_path(glob->path);
	if (glob->cmd)
		free_cmd(glob->cmd);
	if (glob->token_list)
		free_tok(&glob->token_list);
	if (glob->line)
		free(glob->line);
	free(glob);
	rl_clear_history();
	if (str)
		ft_putstr_fd(str, 2);
	exit(exit_val);
}

/*
 * Le nom de la fonction a tout dit
 */
void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

/*
 * Le nom de la fonction a tout dit
 */
void	free_env(t_env *a)
{
	t_env	*tmp;

	if (a == NULL)
		return ;
	while (a)
	{
		tmp = a->next;
		if (a->name)
			free(a->name);
		if (a->value)
			free(a->value);
		if (a->str)
			free(a->str);
		free(a);
		a = tmp;
	}
}

/*
 * Le nom de la fonction a tout dit
 */
static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}

/*
 * Le nom de la fonction a tout dit
 */
void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd_args)
			free_args(tmp->cmd_args);
		if (tmp->cmd)
			free(tmp->cmd);
		free(tmp);
	}
}
