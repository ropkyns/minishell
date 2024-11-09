/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:02 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/07 18:42:10 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
On regarde si la commande dans le path est accessible et executable
 */
char	*handle_absolute_relative_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

/*
Extrait la prochaine sous-chaine de start jusqu'a end.
Alloue de la memoire pour la sous-chaîne et met a jour start.
Si end est NULL, duplique le reste de start et le met a NULL.
 */
static char	*get_next_dir(char **start, char *end)
{
	char	*dir;

	if (end)
	{
		dir = malloc(end - *start + 1);
		if (!dir)
			return (NULL);
		ft_strlcpy(dir, *start, end - *start + 1);
		*start = end + 1;
	}
	else
	{
		dir = ft_strdup(*start);
		*start = NULL;
	}
	return (dir);
}

/*
Recherche un fichier executable correspondant a cmd dans les repertoires
specifies par path_var.
Extrait chaque repertoire separe par : et construit le chemin complet.
Retourne le chemin si trouve, ou NULL en cas d'echec.
 */
static char	*search_command_in_path(char *path_var, char *cmd)
{
	char	*start;
	char	*end;
	char	*dir;
	char	*path_name;

	start = path_var;
	while (start)
	{
		end = ft_strchr(start, ':');
		dir = get_next_dir(&start, end);
		if (!dir)
			return (NULL);
		path_name = build_path(dir, cmd);
		free(dir);
		if (access(path_name, X_OK) == 0)
			return (path_name);
		free(path_name);
	}
	return (NULL);
}

/*
Obtient le chemin d'une commande cmd.
Si la commande est vide, absolue ou relative traite en consequence.
Sinon, elle recupere la variable d'environnement "PATH" et recherche
la commande dans les repertoires specifies.
Retourne le chemin de la commande ou NULL si introuvable.
 */
char	*get_command_path(char *cmd, t_env *env_list)
{
	char	*path_var;

	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (handle_absolute_relative_path(cmd));
	path_var = get_env_value(env_list, "PATH");
	if (!path_var)
		return (NULL);
	return (search_command_in_path(path_var, cmd));
}
