/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:24:50 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/18 14:57:46 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*init_env(char **env)
{
	t_env	*current;
	t_env	*tmp;
	int		i;

	i = -1;
	current = NULL;
	current->prev = NULL;
	while (env[++i])
	{
		current->str = strdup(env[i]);
		printf("%s\n", current->str);
		tmp = current;
		current = current->next;
		current->prev = tmp;
	}
	current->next = NULL;
	while (current->prev)
		current = current->prev;
	return (current);
}
