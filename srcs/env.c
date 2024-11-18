/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:24:50 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/18 12:09:03 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* PENSER A INIT t_env *list AVANT D'APPELER INIT ENV !!!!!!!!!! */

/*
 * Fonction du Q qui copy jusqu'a un delimiteur
 */
char	*ft_strcpychr(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	dest = malloc(sizeof(char) * (i + 1));
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

/*
* Ici on initialise les variables de la liste a NULL,
ensuite on va chercher le nom de la variable d'env
grace a une fonction homemade strcpychr (en gros tu copies
jusqu'a une occurence, ici "=")
ensuite on strdup la valeur, qui se trouve apres equal_sign
*/
static void	set_env(t_env *env)
{
	char	*equal_sign;

	env->name = NULL;
	env->value = NULL;
	env->next = NULL;
	env->is_freed = false;
	env->name = ft_strcpychr(env->name, env->str, '=');
	if (env->name == NULL)
	{
		return ;
	}
	equal_sign = ft_strchr(env->str, '=');
	if (equal_sign)
	{
		free(env->value);
		env->value = ft_strdup(equal_sign + 1);
	}
}

/*
 * Ici on va parcourir la liste pour trouver et return la derniere node
 */
static t_env	*find_last_node_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

/*
* Fonction pour ajouter nos nodes dans la liste chainee,
on va recuperer la ligne du tab env et la stocker dans ->str
ensuite on fait en sorte que la node soit bien chainee avec le
bon prev/next (cas special si c'est la premiere node)
*/
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

/*
 * Ici on initialise notre liste chainee des env (on ajoute les nodes)
 */
void	init_env(t_env **current, char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return ;
	while (env[i])
	{
		add_node_env(current, env[i]);
		i++;
	}
}
