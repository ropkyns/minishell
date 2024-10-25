/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:29:04 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/25 15:59:21 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Fonction pour initialiser notre struct global :)
 */
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

/*
 * Fonction de debuggage, on peut voir et afficher le type des tokens!
 */
void	print_token(t_structok *token)
{
	t_structok	*tmp;

	if (!token)
		return ;
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

/*
 * Fonction de debuggage, on print les cmd !
 */
// void	print_cmd(t_cmd *cmd)
// {

// 	if (!cmd)
// 		return ;
// 	printf("PRINT CMD !\n");
// 	fflush(stdout);
// 	while (cmd)
// 	{

// 		printf("%s", cmd->cmd);
// 		fflush(stdout);
// 		cmd = cmd->next;
// 	}
// 	printf("\n");
// 	fflush(stdout);
// }

/*
 * La maison mere un peu, genre mother💅
 */
int	main(int argc, char **argv, char **env)
{
	t_global	*glob;

	glob = malloc(sizeof(t_global));
	init_global(glob, argc, argv, env);
	init_env(&glob->env, env);
	isatty(1);
	while (1)
	{
		handle_signal();
		glob->cmd = NULL;
		glob->line = readline("minishell > ");
		if (!(glob->line))
			error_exit("exit", glob);
		add_history(glob->line);
		if (!do_list_token(&glob->token_list, glob->line))
			return (1);
		if (check_syntax(glob, &glob->token_list) == true)
		{
			print_token(glob->token_list);
			init_cmd(&glob->cmd, &glob->token_list, glob);
			if (glob && glob->cmd && glob->cmd->cmd_args)
				get_cmd(glob->cmd, &glob, &glob->env);
		}
		free_cmd(glob->cmd);
		free(glob->line);
		free_tok(&glob->token_list);
	}
	return (1);
}
