/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:25:10 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/18 11:44:56 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* OK alors la l'exec fait que quand on appelle une fonction qui n'est pas un builtin ca exit notre programme...
et ca on veut pas et je pense que c'est parce que execve ne revient pas quand il reussit et il exit,
donc il faudrait execve dans un child process comme ca il ferme le child et pas notre programme.
en plus de ca on peut gerer les pipe et tout ici
*/

/*
* Execve dans un child process si il n'y a pas de pipe
(une seule commande en gros)
*/
void	execute_simple(t_cmd *cmd, char *path_name, t_env **env)
{
	pid_t	pid;
	char	**env_array;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		env_array = make_env_tab(env);
		if (!env_array)
			exit(1);
		if (execve(path_name, cmd->cmd_args, env_array) == -1)
		{
			free(env_array);
			exit(1);
		}
		free(env_array);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

/*
* Execve mais avec des pipes, on redirige les stdin stdout avec dup2 et pipe
tant qu'il y a une autre commande il y aura un autre pipe (-1)
*/

// void	child_process(t_cmd *cmd, pid_t pid, t_global *glob, t_env **env,
// 		int **pipes)
// {
// if (cmd->infile != STDIN_FILENO)
// {
// 	if (dup2(cmd->infile, STDIN_FILENO) == -1)
// 		error_exit("dup2 infile error", glob);
// 	close(cmd->infile);
// }
// if (cmd->next)
// {
// 	if (dup2(pipes[1], STDOUT_FILENO) == -1)
// 		error_exit("dup2 pipe[1] error", glob);
// 	close(pipes[0]);
// }
// handle_redir(cmd);
// execve(cmd->cmd, cmd->cmd_args, env);
// error_exit("execve error", glob);
// }

// void	execute_piped(t_cmd *cmd, t_env **env, t_global *glob)
// {
// 	int		pipes[2];
// 	pid_t	pid;
// 	char	**env_array;

// 	while (cmd)
// 	{
// 		if (cmd->next)
// 		{
// 			if (pipe(pipes) == -1)
// 				error_exit("pipe error", glob);
// 			cmd->outfile = pipes[1];
// 		}
// 		pid = fork();
// 		if (pid < 0)
// 			error_exit("fork error", glob);
// 		if (pid == 0)
// 		{
// 			if (cmd->infile != STDIN_FILENO)
// 			{
// 				dup2(cmd->infile, STDIN_FILENO);
// 				close(cmd->infile);
// 			}
// 			if (cmd->outfile != STDIN_FILENO)
// 			{
// 				dup2(cmd->outfile, STDIN_FILENO);
// 				close(cmd->outfile);
// 			}
// 			if (cmd->next)
// 				close(pipes[0]);
// 			handle_redir(cmd);
// 			env_array = make_env_tab(env);
// 			if (!env_array)
// 				exit(1);
// 			if (is_builtins(cmd->cmd_args[0]))
// 				get_builtins(cmd, env, &glob);
// 			else
// 				execve(cmd->cmd, cmd->cmd_args, env_array);
// 			free(env_array);
// 			exit(0);
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 			if (cmd->next)
// 				close(pipes[1]);
// 			if (cmd->infile != STDIN_FILENO)
// 				close(cmd->infile);
// 			cmd = cmd->next;
// 		}
// 	}
// }

void	execute_piped(t_cmd *cmd, t_env **env, t_global *glob)
{
	int		pipes[2];
	pid_t	pid;
	char	**env_array;
	int		input_fd;

	input_fd = STDIN_FILENO;
	while (cmd)
	{
		// Crée un pipe si la commande suivante existe
		if (cmd->next)
		{
			if (pipe(pipes) == -1)
			{
				perror("pipe error");
				exit(1);
			}
			printf("Created pipe: read end = %d, write end = %d\n", pipes[0],
				pipes[1]);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		if (pid == 0) // Processus enfant
		{
			printf("In child process: %s\n", cmd->cmd_args[0]);
			// Redirection de l'entrée
			if (input_fd != STDIN_FILENO)
			{
				if (dup2(input_fd, STDIN_FILENO) == -1)
				{
					perror("dup2 input_fd error");
					exit(1);
				}
				close(input_fd);
			}
			// Redirection de la sortie
			if (cmd->next)
			{
				if (dup2(pipes[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 pipes[1] error");
					exit(1);
				}
				close(pipes[1]);
			}
			close(pipes[0]); // Ferme la lecture dans le pipe
			// Gestion des redirections de fichiers
			handle_redir(cmd);
			printf("About to execute: %s\n", cmd->cmd_args[0]); // Debug print
			env_array = make_env_tab(env);
			if (!env_array)
			{
				perror("env_array allocation error");
				exit(1);
			}
			// Exécution de la commande
			if (is_builtins(cmd->cmd_args[0]))
			{
				get_builtins(cmd, env, &glob);
			}
			else
			{
				execve(cmd->cmd, cmd->cmd_args, env_array);
				perror("execve error"); // Message d'erreur si execve échoue
			}
			free(env_array);
			exit(1); // Sortir avec une erreur si execve échoue
		}
		else // Processus parent
		{
			close(pipes[1]);       // Fermer le descripteur d'écriture
			input_fd = pipes[0];  
				// Préparer l'entrée pour la prochaine commande
			waitpid(pid, NULL, 0); // Attendre la fin du processus enfant
			// Fermer cmd->infile s'il n'est pas STDIN_FILENO
			if (cmd->infile != STDIN_FILENO)
				close(cmd->infile);
			cmd = cmd->next; // Passer à la commande suivante
		}
	}
}

void	handle_redir(t_cmd *cmd)
{
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			perror("dup2 infile error");
		close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			perror("dup2 outfile error");
		close(cmd->outfile);
	}
}
