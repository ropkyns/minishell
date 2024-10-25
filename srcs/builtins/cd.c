/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/25 17:28:50 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Calcule la taille de la liste env
 */
static int	envsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
/*
*parcourt la liste des variables d'environnement pour trouver la valeur actuelle de PWD
Si PWD est trouve, sa valeur est prefix par "OLD" et donner a OLDPWD.
Si PWD n'est pas trouve, OLDPWD est initialise avec une valeur par defaut.
ENfin on free check.
 */
static void	update_old_pwd(t_global *glob)
{
	t_env	*temp;
	char	*check;
	int		len;

	temp = glob->env;
	check = NULL;
	len = envsize(temp);
	while (len--)
	{
		if (ft_strncmp(temp->str, "PWD=", 4) == 0)
			check = temp->str;
		temp = temp->next;
	}
	if (!check)
		export_value(&glob->env, "OLDPWD");
	if (check)
	{
		check = ft_strjoin("OLD", check);
		if (!check)
			return ;
		export_value(&glob->env, check);
	}
	free(check);
}
/*
 *  On sauvegarde OLDPWD en appelant updatde-old
 ensuite on utilise getcwd pour recuperer notre pwd
 on va ensuite le join a PWD=.
 on export tout ca dans la liste des env
 Enfin on free
 */
static void	update_pwd(t_global *glob, char *args)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_old_pwd(glob);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(args);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
	{
		printf("malloc error\n");
		return ;
	}
	export_value(&glob->env, pwd);
	free(pwd);
}
/*
* On compte le nombre d'arguments (il en faut 2, la cmd et l'arg)
on change de directory avec la fonction chdir, si ca a marche on update PWD
(qui va update OLD pwd aussi)
sinon perror (genre si le directory existe po)
*/
int	ft_cd(t_global *glob, char **args)
{
	int	ret;
	int	count;

	count = 0;
	while (args[count])
		count++;
	if (count == 2)
	{
		ret = chdir(args[1]);
		if (ret == 0)
			update_pwd(glob, args[1]);
		if (ret < 0)
			perror(args[1]);
		return (ret);
	}
	return (1);
}
