/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:44:03 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/12 14:29:07 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Calcule la taille de la liste env
 on commence i a 1 car on est pas bete et si on arrive ici
 c'est que la liste est pas vide
 */
size_t	len_env(t_env *env)
{
	t_env	*tmp;
	size_t	i;

	if ((env))
	{
		tmp = env;
		i = 1;
		while (tmp->next != NULL)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

/*
 * On print
 */
int	ft_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	if (!temp)
		return (0);
	if (ft_strchr(temp->str, '='))
		printf("%s\n", temp->str);
	temp = temp->next;
	while (temp != NULL)
	{
		if (ft_strchr(temp->str, '='))
			printf("%s\n", temp->str);
		temp = temp->next;
	}
	return (0);
}
