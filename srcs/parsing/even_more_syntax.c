/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/23 15:57:04 by mjameau          ###   ########.fr       */
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

static bool	check_is_dollar(char *value)
{
	if (value[0] == '$')
		return (true);
	else
		return (false);
}

void	check_dollar_sign(t_structok **toklist, t_env *env)
{
	t_structok	*tmp;

	if (!toklist || !(*toklist))
		return ;
	tmp = (*toklist);
	while (tmp->next)
	{
		if (check_is_dollar(tmp->value))
		{
			tmp->value = ft_strdup(search_env(tmp->value + 1, env));
		}
		tmp = tmp->next;
		if (tmp == (*toklist))
			break ;
	}
}
