/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:24:50 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/24 16:45:19 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* PENSER A INIT t_env *list AVANT D'APPELER INIT ENV !!!!!!!!!! */

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
		free(current);
		current = tmp;
	}
}

void	print_env(t_env *env)
{
	while (env->next)
	{
		printf("%s\n", env->str);
		env = env->next;
	}
}

t_env	*find_last_node_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_node_env(t_env **env, char *value)
{
	t_env		*node;
	t_env		*last_node;

	if (env == NULL)
		return ;
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->next = NULL;
	node->str = value;
	if (*env == NULL)
	{
		node->prev = NULL;
		*env = node;
	}
	else
	{
		last_node = find_last_node(*env);
		node->prev = last_node;
		last_node->next = node;
	}
}

void	init_env(t_env	**current, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		add_node_env(current, env[i]);
		i++;
	}
}

/* int	main(int ac, char **av, char **env)
{
	t_env	*list;

	list = NULL;
	init_env(&list, env);
	print_env(list);
	free_env(list);
	return (0);
} */
