/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:59:38 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/02 16:22:05 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_first_pipe(t_structok **tok_list, t_global *glob)
{
	if ((*tok_list)->type == PIPE)
	{
		glob->exit_value = 2;
		return (true);
	}
	else
		return (false);
}

bool	is_last_pipe(t_structok **tok_list, t_global *glob)
{
	while ((*tok_list)->next)
		(*tok_list) = (*tok_list)->next;
	if ((*tok_list)->type == PIPE)
	{
		glob->exit_value = 2;
		return (true);
	}
	else
		return (false);
}

bool	check_quotes(bool *double_quote, bool *single_quote, int *pos, char c)
{
	if (c == '"' && !*single_quote)
		*double_quote = !*double_quote;
	else if (c == '\'' && !*double_quote)
		*single_quote = !*single_quote;
	(*pos)++;
	return (false);
}

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

void	check_syntax(t_global *glob, t_structok **token_list)
{
	if (handle_quotes(glob, glob->line) == true)
		error_exit("bash: syntax error quotes aren't closed", glob);
	else if (is_first_pipe(token_list, glob) == true)
		error_exit("bash: syntax error near unexpected token `|'", glob);
	else if (is_op_before_pipe(token_list, glob))
		error_exit("bash: syntax error near unexpected token `|'", glob);
	else if (is_last_pipe(token_list, glob))
		error_exit("bash: syntax error near unexpected token `|'", glob);
	else if (is_op_after_op(token_list, glob))
		error_exit("", glob);
	else if (is_last_op(token_list, glob))
		error_exit("syntax error near unexpected token `newline'", glob);
}
