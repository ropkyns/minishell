/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:25:10 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/22 19:34:41 by mjameau          ###   ########.fr       */
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

	printf("TEST");
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

void	execute_piped(t_cmd *cmd, t_env **env, t_global *glob)
{
	int		pipes[2];
	pid_t	pid;
	char	**env_array;
	char	*path_name;

	(void)glob;
	int input_fd = STDIN_FILENO; // Start with standard input
	while (cmd)
	{
		// Create a pipe only if it's not the last command
		if (cmd->next && pipe(pipes) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		pid = fork(); // Create a new process
		if (pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		if (pid == 0) // In child process
		{
			// Redirect input if needed
			if (input_fd != STDIN_FILENO)
			{
				if (dup2(input_fd, STDIN_FILENO) == -1)
				{
					perror("dup2 input_fd error");
					exit(1);
				}
				close(input_fd); // Close the old input_fd
			}
			// Redirect output if this is not the last command
			if (cmd->next)
			{
				if (dup2(pipes[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 pipes[1] error");
					exit(1);
				}
			}
			// Close the read end of the pipe
			close(pipes[0]);
			// Handle redirection from infile and outfile if set
			if (cmd->infile != -1)
			{
				if (dup2(cmd->infile, STDIN_FILENO) == -1)
				{
					perror("dup2 infile error");
					exit(1);
				}
				close(cmd->infile);
			}
			if (cmd->outfile != -1)
			{
				if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
				{
					perror("dup2 outfile error");
					exit(1);
				}
				close(cmd->outfile);
			}
			// Fetch the environment array
			env_array = make_env_tab(env);
			if (!env_array)
			{
				perror("env_array allocation error");
				exit(1);
			}
			// Retrieve the path for the command
			path_name = get_command_path(cmd->cmd_args[0], *env);
			if (!path_name)
			{
				fprintf(stderr, "Command not found: %s\n", cmd->cmd_args[0]);
				free(env_array);
				exit(127); // Command not found
			}
			// Execute the command
			execve(path_name, cmd->cmd_args, env_array);
			perror("execve error"); // If execve fails
			free(env_array);
			free(path_name);
			exit(1);
		}
		else // In parent process
		{
			close(pipes[1]); // Close the write end of the pipe
			if (input_fd != STDIN_FILENO)
				close(input_fd);   // Close the old input_fd
			input_fd = pipes[0];   // Update input_fd for the next command
			waitpid(pid, NULL, 0); // Wait for the child process to finish
		}
		cmd = cmd->next; // Move to the next command
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
