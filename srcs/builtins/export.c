/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/25 18:16:03 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Si la fonction export n'a pas d'arguments
alors on affiche tout env avec declare -x devant
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

/*
* On regarde si le nom de la variable commence bien par un alpha
ou un _, ensuite on regarde si la valeur de la variable n'a bien que
des alnum ou un _
*/
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

/*
 *  On verifie si str existe dans la liste chainee des env
 on parcourt la liste et on retourne l'index de la variable (j)
 si on la trouve
 */
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
	if (!ft_strncmp(tmp->str, str, i) && (tmp->str[i] == '\0'
			|| tmp->str[i] == '='))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->str, str, i) && (tmp->str[i] == '\0'
				|| tmp->str[i] == '='))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

/*
* Fonction pour export la value,
	on verifie si la variable existe (et si oui a quel index)
et on va a cet index, on free sa value et on la met a jour.
 Si elle existe pas on ajoute une nouvelle node
*/
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

/*
* Si pas d'arguments on affiche toutes les variables d'env, sinon on check
si la syntaxe est valide et ensuite on export!
*/
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
