/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palu <palu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:24:50 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/19 16:44:40 by palu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		printf("%s\n", current->str);
		fflush(stdout);
		tmp = current;
		/* printf("test\n");
		fflush(stdout); */
		current->next = malloc(sizeof(t_env));
		current = current->next;
		/* printf("test\n");
		fflush(stdout); */
		current->prev = tmp;
		/* printf("test\n");
		fflush(stdout); */
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
