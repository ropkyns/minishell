/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:29:04 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/11 11:11:37 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_global(t_global *glob, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	glob->env = NULL;
	glob->line = NULL;
	glob->token_list = NULL;
	glob->cmd = NULL;
	glob->path = init_path(env);
	glob->exit_value = 0;
}

void	print_token(t_structok *token)
{
	t_structok	*tmp;

	tmp = token;
	while (tmp->next != token)
	{
		printf("Type : %d, [%s]\n", tmp->type, tmp->value);
		fflush(stdout);
		tmp = tmp->next;
	}
	printf("Type : %d, [%s]\n", tmp->type, tmp->value);
	fflush(stdout);
}

// BON, pour que get_cmd et tout l'exec marche il faut que dans la liste des cmd
// on prenne en compte **cmd_args (ajoute dans la structure)
int	main(int argc, char **argv, char **env)
{
	t_global	*glob;

	glob = malloc(sizeof(t_global));
	init_global(glob, argc, argv, env);
	init_env(&glob->env, env);
	isatty(1);
	while (1)
	{
		glob->cmd = NULL;
		fflush(stdout);
		glob->line = readline("minishell > ");
		if (!(glob->line))
			error_exit("exit", glob);
		add_history(glob->line);
		if (!do_list_token(&glob->token_list, glob->line))
			return (1);
		print_token(glob->token_list);
		init_cmd(&glob->cmd, &glob->token_list, glob);
		get_cmd(glob->cmd->cmd_args, &glob, &glob->env);
		free_cmd(glob->cmd);
	}
	return (1);
}
