/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:18 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/23 15:57:38 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_syntax(char *value)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, value, strlen(value));
	write(2, "'\n", 2);
}

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
			print_error_syntax((*tok_list)->next->value);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}
