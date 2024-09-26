/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:33:24 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/26 15:41:02 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_exit(char *str, t_global *glob)
{
	free_env(glob->env);
	free_path(glob->path);
	if (glob->cmd)
		free_cmd(glob->cmd);
	if (glob->token_list)
		free_tok(&glob->token_list);
	if (glob->line)
		free(glob->line);
	rl_clear_history();
	printf("%s", str);
	exit(1);
}

void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

void	free_env(t_env *a)
{
	t_env		*tmp;
	t_env		*current;

	if (a == NULL)
		return ;
	current = a;
	while (current)
	{
		tmp = current->next;
		free(current->name);
		free(current->value);
		if (current->str != NULL)
			free(current->str);
		free(current);
		current = tmp;
	}
}

void	free_cmd(t_cmd *a)
{
	t_cmd		*tmp;
	t_cmd		*current;

	if (a == NULL)
		return ;
	current = a;
	while (current)
	{
		tmp = current->next;
		free(current->cmd);
		if (current->infile)
			close(current->infile);
		if (current->outfile)
			close(current->outfile);
		free(current);
		current = tmp;
	}
}
