/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:59:38 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/24 12:59:08 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_first_pipe(t_structok **tok_list)
{
	if ((*tok_list) == PIPE)
		return (true);
	else
		return (false);
}

bool	is_last_pipe(t_structok **tok_list)
{
	while ((*tok_list)->next)
		(*tok_list) = (*tok_list)->next;
	if ((*tok_list) == PIPE)
		return (true);
	else
		return (false);
}
