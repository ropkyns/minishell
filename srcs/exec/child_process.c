/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:25:10 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/20 14:28:30 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* ici c'est pour execve les commandes de execute_piped
on fait le path et on appelle execve
*/
static void	execute_command(t_cmd *cmd, t_env **env)
{
	char	**env_array;
	char	*path_name;

	env_array = make_env_tab(*env);
	if (!env_array)
		exit(1);
	path_name = handle_absolute_relative_path(cmd->cmd_args[0]);
	if (!path_name)
	{
		path_name = get_command_path(cmd->cmd_args[0], *env);
	}
	if (!path_name)
	{
		fprintf(stderr, "Command not found: %s\n", cmd->cmd_args[0]);
		free(env_array);
		exit(127);
	}
	execve(path_name, cmd->cmd_args, env_array);
	perror("execve error");
	free(env_array);
	free(path_name);
	exit(1);
}

/*
 * redirige l'entree standard STDIN a partir de input_fd,
si ce n'est pas l'entree par défaut, si il y a une autre cmd
on redirige la sortie standard STDOUT dans le pipe.
On gere aussi les fd ici (avec infile et oufile), meme principe.
On les ferme bien a chaque fois
 */
void	handle_redirections(t_cmd *cmd, int input_fd, int *pipes)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			exit(1);
		close(input_fd);
	}
	if (cmd->next)
	{
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	close(pipes[0]);
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			exit(1);
		close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			exit(1);
		close(cmd->outfile);
	}
}

/*
* Le pere, il ferme le pipe d'ecriture, et si input_fd n'est pas l'entree
standard STDIN on le ferme, ensuite on fait pointer input_fd vers le pipe
de lecture comme ca le pere peut lire la sortie de commande de l'enfant
*/
static void	handle_parent_process(int *input_fd, int *pipes, pid_t pid)
{
	(void)pid;
	close(pipes[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	*input_fd = pipes[0];
}

/*
* Ici c'est l'enfant, on le fait gerer les redirections, si c'est un builtin on
lance le builtin d'abord ensuite on execve dans execute command
*/
void	execute_child_process(t_cmd *cmd, t_global *glob, int input_fd,
		int *pipes)
{
	signal(SIGQUIT, SIG_DFL);
	handle_redirections(cmd, input_fd, pipes);
	if (is_builtins(cmd->cmd_args[0]))
	{
		launch_builtin(glob, cmd);
		exit(0);
	}
	execute_command(cmd, &glob->env);
}

/*
* On regarde bien si il y a une commande apres, et du coup on cree un pipe.
on regarde si il ya des builtin qui touche aux env et si
c'est le cas on les appelle
ensuite on fork, on appelle le child_process dans le pid 0,
et le pere dans l'autre. on passe a la commande suivante et on recommence
*/
void	execute_piped(t_cmd *cmd, t_env **env, t_global *glob)
{
	int		pipes[2];
	pid_t	pid;
	int		input_fd;

	(void)env;
	input_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && pipe(pipes) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			execute_child_process(cmd, glob, input_fd, pipes);
		else
			handle_parent_process(&input_fd, pipes, pid);
		cmd = cmd->next;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_nl);
	signal(SIGQUIT, handle_nl);
	while (wait(NULL) > 0)
		;
	signal(SIGINT, SIG_DFL);
}
