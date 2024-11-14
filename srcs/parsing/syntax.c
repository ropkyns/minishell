/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:59:38 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/12 15:09:23 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Pour le $, si $? alors on va chercher l'exit value
sinon on va chercher la value (ex echo $PWD - > truc/truc/minishell)
*/
char	*search_env(char *value, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(value, env->name) == 0)
		{
			free(value);
			value = ft_strdup(env->value);
			return (value);
		}
		env = env->next;
	}
	free(value);
	return (ft_strdup("\0"));
}

/*
* Fonction qui va appeler toutes nos petites fonctions "specialises"
pour les erreurs de syntaxe, en fonction de l'erreur on affiche le mssg
approprie.
*/
bool	check_syntax(t_global *glob, t_structok **token_list)
{
	if (is_first_pipe(token_list, glob))
		return (printf("bash: syntax error near unexpected token `|'\n"),
			false);
	else if (is_last_pipe(token_list, glob))
		return (printf("bash: syntax error near unexpected token `|'\n"),
			false);
	else if (is_op_before_pipe(token_list, glob))
		return (printf("bash: syntax error near unexpected token `|'\n"),
			false);
	else if (is_op_after_op(token_list, glob))
		return (false);
	else if (is_last_op(token_list, glob))
		return (printf("syntax error near unexpected token `newline'\n"),
			false);
	else if (is_invalid(token_list, glob))
		return (false);
	else
		return (true);
}
