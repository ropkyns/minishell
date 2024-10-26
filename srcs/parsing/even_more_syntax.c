/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/26 19:17:22 by paulmart         ###   ########.fr       */
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

void	replace_dollar(char *line, t_env *env, t_global *glob)
{
	int		i;
	char	variable;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			search_env(line, env, glob);
		}
	}
}

/*
	Fonction mere,
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
		replace_dollar(tmp->value, env, glob);
		tmp = tmp->next;
		if (tmp == (*toklist))
			break ;
	}
}
