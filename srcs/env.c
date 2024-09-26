/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:24:50 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/26 16:06:05 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* PENSER A INIT t_env *list AVANT D'APPELER INIT ENV !!!!!!!!!! */

char	*ft_strcpychr(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	set_env(t_env *env)
{
	int		i;
	char	*equal_sign;

	i = 0;
	env->name = NULL;
	env->value = NULL;
	env->next = NULL;
	env->name = ft_strcpychr(env->name, env->str, '=');
	if (env->name == NULL)
	{
		return ;
	}
	equal_sign = ft_strchr(env->str, '=');
	if (equal_sign)
		env->value = ft_strdup(equal_sign + 1);
}

static t_env	*find_last_node_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

bool	add_node_env(t_env **env, char *value)
{
	t_env	*node;
	t_env	*last_node;

	if (env == NULL)
		return (false);
	node = malloc(sizeof(t_env));
	if (!node)
		return (false);
	node->str = ft_strdup(value);
	if (!node->str)
		return (false);
	// node->str = value;
	set_env(node);
	if (*env == NULL)
	{
		node->prev = NULL;
		*env = node;
	}
	else
	{
		last_node = find_last_node_env(*env);
		node->prev = last_node;
		last_node->next = node;
	}
	return (true);
}

void	init_env(t_env **current, char **env)
{
	int	i;

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
