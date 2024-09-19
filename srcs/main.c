/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palu <palu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:29:04 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/19 16:30:58 by palu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_global(t_global *glob, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	glob->env = NULL;
	glob->line = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_global	*glob;

	glob = malloc(sizeof(t_global));
	init_global(glob, argc, argv);
	glob->env = init_env(env);
	isatty(1);
	while (1)
	{
		glob->line = readline("minishell > ");
		if (!(glob->line))
			return (1); //TODO cas d'erreur
		add_history(glob->line);
	}
	return (1);
}
