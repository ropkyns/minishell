/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/26 12:09:23 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Pour le $, si $? alors on va chercher l'exit value
sinon on va chercher la value (ex echo $PWD - > truc/truc/minishell)
*/
char	*search_env(char *value, t_env *env, t_global *glob)
{
	char	*ret;

	ret = "\0";
	if (ft_strcmp(value, "?") == 0)
		return (ft_itoa(glob->exit_value));
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

/*
 * J'pense que le nom de la fonction suffit
 */
static bool	check_is_dollar(char *value)
{
	if (value[0] == '$')
		return (true);
	else
		return (false);
}

/*
* Fonction mere,
	on check si il y a un signe dollar et si oui on l'envoie dans search_env
et on strdup la valeur (ou l'exit value)
*/
void	check_dollar_sign(t_structok **toklist, t_env *env, t_global *glob)
{
	t_structok	*tmp;

	if (!toklist || !(*toklist))
		return ;
	tmp = (*toklist);
	while (tmp->next)
	{
		if (check_is_dollar(tmp->value))
		{
			tmp->value = ft_strdup(search_env(tmp->value + 1, env, glob));
		}
		tmp = tmp->next;
		if (tmp == (*toklist))
			break ;
	}
}
