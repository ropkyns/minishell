/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:33:24 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/10 12:44:31 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_exit(char *str, t_global *glob)
{
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
	rl_clear_history();
	if (str)
		ft_putstr_fd(str, 2);
	exit(glob->exit_value);
}

void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

// void	free_env(t_env *a)
// {
// 	t_env	*tmp;
// 	t_env	*current;

// 	if (a == NULL)
// 		return ;
// 	current = a;
// 	while (current)
// 	{
// 		tmp = current->next;
// 		free(current->name);
// 		free(current->value);
// 		if (current->str != NULL)
// 			free(current->str);
// 		free(current);
// 		current = tmp;
// 	}
// }

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

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

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
