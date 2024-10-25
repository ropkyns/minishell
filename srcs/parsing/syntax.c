/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:59:38 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/25 18:24:22 by mjameau          ###   ########.fr       */
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
bool	check_quotes(bool *double_quote, bool *single_quote, int *pos, char c)
{
	if (c == '"' && !*single_quote)
		*double_quote = !*double_quote;
	else if (c == '\'' && !*double_quote)
		*single_quote = !*single_quote;
	(*pos)++;
	return (false);
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
		check_quotes(&double_quote, &single_quote, &pos, command[pos]);
	if (double_quote || single_quote)
	{
		data->exit_value = 2;
		return (true);
	}
	data->exit_value = 0;
	return (false);
}

/*
* Fonction qui va appeler toutes nos petites fonctions "specialises"
pour les erreurs de syntaxe, en fonction de l'erreur on affiche le mssg
approprie.
*/
bool	check_syntax(t_global *glob, t_structok **token_list)
{
	check_dollar_sign(token_list, glob->env, glob);
	if (handle_quotes(glob, glob->line))
		return (printf("bash: syntax error quotes aren't closed\n"), false);
	else if (is_first_pipe(token_list, glob))
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
	else
		return (true);
}
