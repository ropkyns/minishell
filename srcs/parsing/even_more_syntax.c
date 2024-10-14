/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/14 15:26:56 by paulmart         ###   ########.fr       */
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
			break ;
		}
		env = env->next;
	}
	return (ret);
}

void	check_dollard_sign(t_structok **toklist, t_env *env, t_global *glob)
{
	t_structok	*tmp;

	tmp = (*toklist);
	while (tmp->next != (*toklist))
	{
		if (tmp->value[0] == '$')
			tmp->value = search_env(tmp->value, env);
		tmp = tmp->next;
	}
}
