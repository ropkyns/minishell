/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:18 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/02 16:13:52 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_last_op(t_structok **tok_list, t_global *glob)
{
	while ((*tok_list)->next)
		(*tok_list) = (*tok_list)->next;
	if ((*tok_list)->type == INPUT || (*tok_list)->type == OUTPUT
		|| (*tok_list)->type == HEREDOC || (*tok_list)->type == APPEND)
	{
		glob->exit_value = 2;
		return (true);
	}
	else
		return (false);
}

bool	is_op_before_pipe(t_structok **tok_list, t_global *glob)
{
	while ((*tok_list)->next)
	{
		while ((*tok_list)->type != PIPE)
			(*tok_list) = (*tok_list)->next;
		if ((*tok_list)->prev->type == INPUT
			|| (*tok_list)->prev->type == OUTPUT
			|| (*tok_list)->prev->type == HEREDOC
			|| (*tok_list)->prev->type == APPEND
			|| (*tok_list)->next->type == PIPE)
		{
			glob->exit_value = 2;
			return (true);
		}
		(*tok_list) = (*tok_list)->next;
	}
	return (false);
}

char	*is_op_after_op(t_structok **tok_list, t_global *glob)
{
	while ((*tok_list)->next)
	{
		while ((*tok_list)->type != PIPE)
			(*tok_list) = (*tok_list)->next;
		if ((*tok_list)->next->type == INPUT
			|| (*tok_list)->next->type == OUTPUT
			|| (*tok_list)->next->type == HEREDOC
			|| (*tok_list)->next->type == APPEND)
		{
			glob->exit_value = 2;
			print_error_syntaxe((*tok_list)->next->value);
			return (true);
		}
		(*tok_list) = (*tok_list)->next;
	}
	return (false);
}

void	print_error_syntax(char *value)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, value, strlen(value));
	write(2, "'\n", 2);
}
