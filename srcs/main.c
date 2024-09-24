/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:29:04 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/24 16:33:08 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_global(t_global *glob, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	glob->env = NULL;
	glob->line = NULL;
	glob->token_list = NULL;
}

void	print_token(t_structok *token)
{
	t_structok	*tmp;

	tmp = token;
	while (tmp->next != token)
	{
		printf("Type : %d, [%s]\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	printf("Type : %d, [%s]\n", tmp->type, tmp->value);
}

int	main(int argc, char **argv, char **env)
{
	t_global	*glob;

	glob = malloc(sizeof(t_global));
	init_global(glob, argc, argv);
	init_env(&glob->env, env);
	isatty(1);
	while (1)
	{
		glob->line = readline("minishell > ");
		if (!(glob->line))
			return (1); // TODO cas d'erreur
		add_history(glob->line);
		if (!do_list_token(&glob->token_list, glob->line))
			return (1);
		print_token(glob->token_list);
	}
	return (1);
}
