/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:24:50 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/23 15:55:40 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(t_env *env)
{
	while (env->next)
	{
		printf("%s\n", env->str);
		env = env->next;
	}
}

t_env	*init_env(char **env)
{
	t_env	*current;
	t_env	*tmp;
	int		i;

	i = -1;
	current = malloc(sizeof(t_env));
	*current = (t_env){0};
	tmp = NULL;
	while (env[++i])
	{
		tmp = malloc(sizeof(t_env));
		current->str = ft_strdup(env[i]);
		tmp = current;
		current->next = malloc(sizeof(t_env));
		current = current->next;
		current->prev = tmp;
		free(tmp->str);
		free(tmp);
	}
	current->next = NULL;
	while (current->prev)
	{
		current = current->prev;
	}
	return (current);
}
