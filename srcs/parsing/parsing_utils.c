/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:00:12 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/18 12:02:05 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Fonction pour regarder si le premier token est un pipe.
 */
bool	is_first_pipe(t_structok **tok_list, t_global *glob)
{
	if (!*tok_list)
		return (false);
	if ((*tok_list)->type == PIPE)
	{
		glob->exit_value = 2;
		return (true);
	}
	else
		return (false);
}

/*
 * Fonction pour regarder si le dernier token est un pipe.
 */
bool	is_last_pipe(t_structok **tok_list, t_global *glob)
{
	t_structok	*tmp;

	if (!(*tok_list))
		return (false);
	tmp = (*tok_list);
	while (tmp->next != (*tok_list))
		tmp = tmp->next;
	if (tmp->type == PIPE)
	{
		glob->exit_value = 2;
		return (true);
	}
	else
		return (false);
}

/*
* Ici notre fonction qui va changer notre variable bool a chaque fois que le char
est une quote.
*/
void	check_quotes(bool *double_quote, bool *single_quote, int *pos, char c)
{
	if ((c == '\'' || c == '"') && !*single_quote && !*double_quote)
	{
		if (c == '\'' && !*double_quote)
			*single_quote = true;
		else if (c == '"' && !*single_quote)
			*double_quote = true;
		if (pos)
			++(*pos);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*double_quote && *single_quote)
			*single_quote = false;
		else if (c == '"' && !*single_quote && *double_quote)
			*double_quote = false;
		if (pos)
			++(*pos);
	}
}

/*
* Ici on va utiliser des booleans qu'on va passer a notre fonction
check_quote pour verifier si nos quotes sont fermees ou non.
on gere l'exit_value en fonction.
*/
bool	handle_quotes(t_global *data, char *command)
{
	bool	single_quote;
	bool	double_quote;
	int		pos;

	pos = 0;
	double_quote = false;
	single_quote = false;
	while (command && command[pos])
	{
		check_quotes(&double_quote, &single_quote, &pos, command[pos]);
		if (command[pos] && command[pos] != '\'' && command[pos] != '"')
			++pos;
	}
	if (double_quote || single_quote)
	{
		ft_putstr_fd("bash: syntax error quotes aren't closed\n", 2);
		data->exit_value = 2;
		return (true);
	}
	return (false);
}

/*
 * gere le cas d'erreur pour les caracteres du CUL
 */
bool	is_invalid(t_structok **tok_list, t_global *glob)
{
	if (!*tok_list)
		return (false);
	if ((*tok_list)->value[0] == '&')
	{
		glob->exit_value = 2;
		return (print_error_syntax((*tok_list)->value), true);
	}
	if ((*tok_list)->value[0] == ':')
	{
		glob->exit_value = 0;
		return (true);
	}
	if ((*tok_list)->value[0] == '!')
	{
		glob->exit_value = 1;
		return (true);
	}
	return (false);
}
