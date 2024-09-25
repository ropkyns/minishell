/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/25 18:32:46 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*
en gros je check si args, si pas d'arguments alors j'affiche tout.
si arguments je regarde si un env->name existe deja sous le meme nom
si il existe deja je prends juste la valeur et remplace l'ancienne
si il existe pas je le creer et lui attribue la valeur.
*/
int	export(t_env *env, char *args)
{
	int		i;
	char	*equal_sign;

	i = 1;
	equal_sign = ft_strchr(&args[i - 1], '=');
	if (!args)
		print_env(env);
	else
	{
		while (env->next != NULL)
		{
			if (ft_strncmp(env->name, &args[i], ft_strlen(env->name)) == 0)
			{
				if (equal_sign)
					env->value = ft_strdup(equal_sign + 1);
			}
			else
				add_node_env(&env, &args[i]);
		}
	}
	return (0);
}

int	main(void)
{
	t_env *env_list = NULL;
	char *args = "";

	// Appel à la fonction export
	export(env_list, args);

	// Afficher la liste d'environnements après l'appel de export
	printf("\nListe des variables d'environnement après export:\n");
	t_env *temp = env_list;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}

	// Libérer la mémoire (si nécessaire)
	return (0);
}