/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:33 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/25 17:46:10 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* MAN : La fonction getcwd() copie le chemin d'acces absolu du
répertoire de travail courant dans la chaîne pointée par cwd,
qui est de longueur PATH_MAX (nb max de path inclus dans limits.h).

On l'affiche ensuite avec printf
Le contenu de la chaine cwd est indefinie en cas d'erreur,
	donc j'ai mit un ptit perror pwd du cul
*/
int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (SUCCESS);
	}
	else
	{
		perror("pwd");
		return (FAIL);
	}
}
