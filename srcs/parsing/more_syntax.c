/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:18 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/18 15:36:24 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Fonction pour verifier si le chemin est un repertoire
 */
bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

/*
 * Affiche l'erreur de syntaxe
 */
void	print_error_syntax(char *value)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, value, ft_strlen(value));
	write(2, "'\n", 2);
}

/*
* Fonction pour regarder si le dernier token est un operateur
( < << >> >)
*/
bool	is_last_op(t_structok **tok_list, t_global *glob)
{
	t_structok	*tmp;

	if (!(*tok_list))
		return (false);
	tmp = (*tok_list);
	while (tmp->next != (*tok_list))
		tmp = tmp->next;
	if (tmp->type == INPUT || tmp->type == OUTPUT || tmp->type == HEREDOC
		|| tmp->type == APPEND)
	{
		glob->exit_value = 2;
		return (true);
	}
	else
		return (false);
}

/*
* Fonction pour regarder si le token avant le pipe est un operateur
(ex ; echo hihi >> | cat -e)
*/
bool	is_op_before_pipe(t_structok **tok_list, t_global *glob)
{
	t_structok	*tmp;

	if (!(*tok_list))
		return (false);
	tmp = (*tok_list);
	while (tmp->next != (*tok_list))
	{
		while (tmp->type != PIPE && tmp->next->next != (*tok_list))
			tmp = tmp->next;
		if (tmp->type == PIPE && (tmp->prev->type == INPUT
				|| tmp->prev->type == OUTPUT || tmp->prev->type == HEREDOC
				|| tmp->prev->type == APPEND || tmp->next->type == PIPE))
		{
			glob->exit_value = 2;
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

/*
* Fonction pour regarder si le token avant l'operateur est
aussi un operateur
(ex ; trucmuche >> >> trucmuche)
*/
bool	is_op_after_op(t_structok **tok_list, t_global *glob)
{
	t_structok	*tmp;

	if (!(*tok_list))
		return (false);
	tmp = (*tok_list);
	while (tmp->next != (*tok_list))
	{
		while ((tmp->type == ARG || tmp->type == CMD)
			&& tmp->next->next != (*tok_list))
			tmp = tmp->next;
		if (tmp->next->type == INPUT || tmp->next->type == OUTPUT
			|| tmp->next->type == HEREDOC || tmp->next->type == APPEND)
		{
			glob->exit_value = 2;
			print_error_syntax(tmp->next->value);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}
