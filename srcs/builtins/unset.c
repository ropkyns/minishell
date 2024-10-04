/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:43 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/02 15:08:21 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* En gros c'est une fonction qui efface une variable dans l'env
(si j'ai bien compris), donc le plan c'est :

prendre la struct env, parcourir la liste des env en regardant leurs name
si le name est identique a celui passe en argument a la fonction unset
alors on free sa value et son name
si ce n'est pas un caractere alphabetique ou un '_' alors afficher erreur
"bash: unset: 'TES*T': not a valid identifier"

Si la variable passe en arg n'existe pas alors ne rien afficher
et exit value a 0.
Si tout se passe bien alors ne rien afficher, et exit value a 0.
*/

static bool	syntax_unset(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '_' || !ft_isalpha(arg[0]))
		return (false);
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	unset(t_env **env, char *args)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	if (!args || !syntax_unset(args))
		return (false);
	while (curr != NULL)
	{
		if (ft_strncmp(curr->name, args, ft_strlen(args) + 1) == 0)
		{
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			free(curr->value);
			free(curr->name);
			free(curr);
			return (true);
		}
		prev = curr;
		curr = curr->next;
	}
	return (false);
}

int	ft_unset(t_env **env, char **args)
{
	int	exit_val;
	int	i;

	exit_val = 0;
	i = 0;
	while (args[i])
	{
		if (unset(env, args[i]))
			exit_val = 1;
	}
	return (exit_val);
}
