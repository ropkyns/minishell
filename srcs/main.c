/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:29:04 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/18 14:35:04 by paulmart         ###   ########.fr       */
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
	char		*rl;
	t_global	glob;


	init_global(&glob, argc, argv);
	glob.env = init_env(env);
	isatty(1);
	while (1)
	{
		glob.line = readline("minishell > ");
		if (!(glob.line))
			return (1); //TODO cas d'erreur
		add_history(rl);
	}
	return (1);
}
