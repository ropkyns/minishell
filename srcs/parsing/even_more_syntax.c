/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/19 17:03:39 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_env(char *value, t_env *env)
{
	char	*ret;

	ret = NULL;
	while (env->next)
	{
		if (ft_strcmp(value, env->name) == 0)
		{
			ret = env->value;
			return (ret);
		}
		env = env->next;
	}
	return (ret);
}

void	check_dollard_sign(t_structok **toklist, t_env *env)
{
	t_structok	*tmp;

	if (!toklist || !(*toklist))
		return ;
	tmp = (*toklist);
	while (tmp->next != (*toklist))
	{
		if (tmp->value[0] == '$')
			tmp->value = search_env(tmp->value, env);
		tmp = tmp->next;
	}
}
	// t_structok	*tmp;

	// if (!toklist || !(*toklist))
	// 	return ;
	// tmp = (*toklist);
	// while (1) // Infinite loop that we manually break from
	// {
	// 	if (tmp->value[0] == '$')
	// 		// tmp->value should be checked to be non-NULL before
	// 		tmp->value = search_env(tmp->value, env);
	// 	// Break if we complete the circular traversal
	// 	if (tmp->next == (*toklist))
	// 		break ;
	// 	tmp = tmp->next;
	// }
