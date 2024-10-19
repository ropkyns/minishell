/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/19 11:58:07 by mjameau          ###   ########.fr       */
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

void	check_dollard_sign(t_structok **toklist, t_env *env)
{
	t_structok	*tmp;

	if (!toklist || !(*toklist)) // Check if the list is NULL
		return ;
	tmp = (*toklist);
	while (1) // Infinite loop that we manually break from
	{
		// Debugging: Check if tmp and tmp->value are valid
		if (!tmp)
		{
			printf("Error: tmp is NULL\n");
			return ;
		}
		if (!tmp->value)
		{
			printf("Error: tmp->value is NULL\n");
			return ;
		}
		// Check if the value starts with a '$'
		if (tmp->value[0] == '$')
			// tmp->value should be checked to be non-NULL before
			tmp->value = search_env(tmp->value, env);
		// Break if we complete the circular traversal
		if (tmp->next == (*toklist))
			break ;
		tmp = tmp->next;
	}
}
