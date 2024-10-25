/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/02 12:45:50 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Si la fonction export n'a pas d'arguments
alors on affiche tout env avec declare -x devant,
(donc on peut pas utiliser print_env :( )
*/
static bool	export_no_args(t_env *env)
{
	char	**arr;
	int		i;
	int		j;

	arr = make_env_tab(env);
	if (!arr)
		return (false);
	sort_array(arr, len_env(env));
	i = 0;
	while (arr[i])
	{
		printf("declare -x ");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);
		if (arr[i][j] && arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free(arr);
	return (true);
}

static bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
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
	int		j;
	t_env	*tmp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	tmp = env;
	if (!ft_strncmp(tmp->str, str, i) && (tmp->str[i] == '\0' || \
		tmp->str[i] == '='))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->str, str, i) && (tmp->str[i] == '\0' || \
			tmp->str[i] == '='))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

bool	export_value(t_env **env, char *str)
{
	int		pos;
	int		i;
	char	*value;

	pos = exist(str, (*env));
	value = ft_strdup(str);
	if (!value)
		return (false);
	if (pos >= 0)
	{
		i = 0;
		while (i < pos)
		{
			(*env) = (*env)->next;
			i++;
		}
		free((*env)->str);
		(*env)->str = value;
	}
	else if (pos == -1)
		if (!add_node_env(env, value))
			return (false);
	return (true);
}

int	ft_export(t_env **env, char **str)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 1;
	if (!str || !str[i])
	{
		if (*env && !export_no_args((*env)))
			return (1);
		return (0);
	}
	while (str[i])
	{
		if (!valid_identifier(str[i]))
		{
			printf("export: invalid identifier\n");
			exit_code = 1;
		}
		else if (!export_value(env, str[i]))
			return (1);
		i++;
	}
	return (exit_code);
}