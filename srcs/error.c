/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:33:24 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/25 17:15:57 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_exit(char *str, t_global *glob)
{
	free_env(glob->env);
	free_cmd(glob->cmd);
	free_tok(&glob->token_list);
	printf("%s", str);
	exit(1);
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
		free(current->str);
		free(current->value);
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
