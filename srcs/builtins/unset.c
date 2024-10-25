/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:43 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/25 14:27:01 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	syntax(char *str)
{
	int	i;

	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	exist(char *str, t_env *env)
{
	int		i;
	t_env	*tmp;
	int		j;

	i = 0;
	tmp = env;
	if (!env)
		return (-1);
	while (str[i])
		i++;
	j = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->str, str, i))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

static bool	unset(char *str, t_env **env)
{
	int		pos;
	t_env	*tmp;
	int		i;

	if (!str || !(*str))
		return (false);
	if (!syntax(str))
		return (printf("unset: invalid identifier\n"), true);
	pos = exist(str, *env);
	if (pos == -1)
		return (false);
	tmp = *env;
	i = -1;
	while (++i < pos)
		tmp = tmp->next;
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	if (tmp == *env)
		*env = tmp->next;
	free(tmp->str);
	free(tmp);
	tmp = NULL;
	return (false);
}

int	ft_unset(t_env **env, char **args)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (args[i])
	{
		if (unset(args[i], env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
