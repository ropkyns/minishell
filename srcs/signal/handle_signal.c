/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:52:56 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/20 13:55:45 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		exit(1);
	}
}

void	handle_nl(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "\n", 1);
	}
}

/*
 * Gere le signal Ctrl-C pour afficher une newline (au lieu de quitter)
 */
void	handle_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
* Le handler, il va attrapper les signaux et decider de quoi faire
en gros ignorer, ou appeler handle_c
*/
void	handle_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_c);
}
