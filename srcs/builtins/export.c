/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/27 10:29:44 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Si la fonction export n'a pas d'arguments
alors on affiche tout env avec declare -x devant,
(donc on peut pas utiliser print_env :( )
*/
static bool	no_args(t_env *env)
{
	while (env != NULL)
	{
		printf("declare -x %s\n", env->str);
		env = env->next;
	}
	return (true);
}

/*
* Ici on regarde si une variable du meme nom existe deja,
on renvoie -1 si elle existe pas, sinon on renvoie sa pos dans la string
ex : export pos1=blabla pos2=blabla
*/
static int	name_already_exist(char *str, t_env *env)
{
	int		i;
	t_env	*temp;
	int		pos;

	temp = env;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!temp)
		return (-1);
	pos = 0;
	while (temp != NULL)
	{
		if (!ft_strncmp(temp->name, str, i)
			&& ((int)ft_strlen(temp->name) == i))
			return (pos);
		temp = temp->next;
		pos++;
	}
	return (-1);
}

/*
* On check la syntaxe, si ca commence par un caractere alpha ou un _
ensuite on regarde si il n'y a bien que des caraceteres alpha ou num
ou un _ dans le nom de la variable (avant le =)
*/
static bool	export_is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (false);
		++i;
	}
	return (true);
}

/*
*
On check si il y a deja une ou des variables du meme nom, si oui
je me deplace de i positions jusqua etre sur le bon env.
Ensuite je free sa value et je la remplace avec ce qu'il y a
apres le signe '=' dans str.
Si pos est egal a -1 alors c'est que aucune variable de ce nom existe,
donc on l'ajoute.
*/
bool	export_value(t_env **env, char *str)
{
	int		i;
	int		pos;
	char	*equal_sign;
	t_env	*curr;
	t_env	*temp;

	curr = *env;
	pos = name_already_exist(str, curr);
	equal_sign = ft_strchr(str, '=');
	if (pos >= 0)
	{
		i = 0;
		temp = curr;
		while (i++ < pos && temp != NULL)
			temp = temp->next;
		if (equal_sign)
		{
			if (temp->value)
				free(temp->value);
			temp->value = ft_strdup(equal_sign + 1);
		}
	}
	else if (pos == -1 && !add_node_env(env, str))
		return (false);
	return (true);
}

/*
* Ici on check si args, si il n'y a rien apres "export" (str[0])
alors on appelle la fonction no_args qui va print notre env.
Si il y a des args, on va appeler notre fonction de check pour voir
si la syntaxe est bonne, et ensuite on va appeler notre fonction
export_value pour voir changer la value si le meme name existe deja
ou alors pour creer une nouvelle variable avec sa value.

(on fait un char **str car plus simple, si la ligne de commande est
 "export test1=blabla test2=blabla test3=blabla",
 on se deplace de maillon en maillon)
*/
int	ft_export(t_env **env, char **str)
{
	int	i;
	int	return_val;

	i = 1;
	return_val = 0;
	if (!str || !str[i])
	{
		if (*env && !no_args((*env)))
			return (printf("malloc error\n"));
		return (0);
	}
	while (str[i])
	{
		if (!export_is_valid(str[i]))
		{
			printf("export : invalid identifier\n");
			return_val = 1;
		}
		else if (!export_value(env, str[i]))
			return (printf("malloc error\n"));
		i++;
	}
	return (return_val);
}
