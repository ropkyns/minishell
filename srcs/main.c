/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:29:04 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/20 13:50:28 by mjameau          ###   ########.fr       */
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
 * Le readline du cul
 */
char	*get_user_input(t_global *glob)
{
	glob->cmd = NULL;
	glob->line = readline("\033[1;35mMinishell > \033[m");
	if (!(glob->line))
		error_exit("exit\n", glob);
	add_history(glob->line);
	return (glob->line);
}

/*
* Appel de fonction pour gerer les quotes, remplacer $ par la valeur,
ensuite fait la liste de token, verifie la syntaxe et va executer la cmd.
*/
void	process_command(t_global *glob)
{
	if (handle_quotes(glob, glob->line) || !replace_dollar(&glob->line,
			glob->env, glob) || !do_list_token(&glob->token_list, glob->line))
		return ;
	if (check_syntax(glob, &glob->token_list) == true)
	{
		init_cmd(&glob->cmd, &glob->token_list, glob);
		if (glob && glob->cmd && glob->cmd->cmd_args)
		{
			get_cmd(glob->cmd, &glob, &glob->env);
		}
	}
}

/*
 * Les freefree
 */
void	cleanup(t_global *glob)
{
	free_cmd(glob->cmd);
	free(glob->line);
	free_tok(&glob->token_list);
}

// void	print_token(t_structok *token)
// {
// 	t_structok	*tmp;

// 	if (!token)
// 		return ;
// 	tmp = token;
// 	while (tmp->next != token)
// 	{
// 		printf("Type : %d, [%s]\n", tmp->type, tmp->value);
// 		fflush(stdout);
// 		tmp = tmp->next;
// 	}
// 	printf("Type : %d, [%s]\n", tmp->type, tmp->value);
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
		get_user_input(glob);
		process_command(glob);
		cleanup(glob);
	}
	return (1);
}
