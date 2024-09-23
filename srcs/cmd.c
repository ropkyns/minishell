/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:22:15 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/23 16:59:11 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*

AAAAAAAAAAAAAAAAAAh on verra plus tard

t_cmd	*init_cmd(t_global *glob)
{
	t_cmd		*cmd;
	t_structok	*tok;
	t_cmd		*tmp;

	tok = glob->token_list;
	cmd = malloc(sizeof(t_cmd));
	cmd->prev = NULL;
	while (tok)
	{
		while (tok->type != CMD)
			tok = tok->next;
		if (tok->type == CMD)
		{
			cmd->cmd = ft_strdup(tok->value);
			cmd->prev = cmd;
			cmd->next = malloc(sizeof(t_cmd));
			cmd = cmd->next;
		}
	}
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}
*/
