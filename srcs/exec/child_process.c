/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:25:10 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/23 15:41:21 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* OK alors la l'exec fait que quand on appelle une fonction qui n'est
pas un builtin ca exit notre programme...
et ca on veut pas et je pense que c'est parce que execve ne revient pas
quand il reussit et il exit,
donc il faudrait execve dans un child process comme ca il ferme le child
et pas notre programme.
en plus de ca on peut gerer les pipe et tout ici
*/

static void	execute_command(t_cmd *cmd, t_env **env)
{
	char	**env_array;
	char	*path_name;

	env_array = make_env_tab(env);
	if (!env_array)
		exit(1);
	path_name = get_command_path(cmd->cmd_args[0], *env);
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

static void	handle_redirections(t_cmd *cmd, int input_fd, int *pipes)
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

static void	handle_parent_process(int *input_fd, int *pipes, pid_t pid)
{
	close(pipes[1]);
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	*input_fd = pipes[0];
	waitpid(pid, NULL, 0);
}

/*
* Execve mais avec des pipes, on redirige les stdin stdout avec dup2 et pipe
tant qu'il y a une autre commande il y aura un autre pipe (-1)
*/
void	execute_piped(t_cmd *cmd, t_env **env, t_global *glob)
{
	int		pipes[2];
	pid_t	pid;
	int		input_fd;

	input_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && pipe(pipes) == -1)
			exit(1);
		if (is_builtins(cmd->cmd_args[0]))
		{
			if (ft_strcmp(cmd->cmd_args[0], "cd") == 0 || ft_strcmp(cmd->cmd_args[0], "export") == 0 || ft_strcmp(cmd->cmd_args[0], "unset") == 0)
			{
				launch_builtin(glob, cmd);
				if (cmd->next)
				{
					input_fd = pipes[0];
					close(pipes[1]);
				}
				cmd = cmd->next;
				continue;
			}
		}
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			handle_redirections(cmd, input_fd, pipes);
			if (is_builtins(cmd->cmd_args[0]))
			{
				launch_builtin(glob, cmd);
				exit(0);
			}
			execute_command(cmd, env);
		}
		else
			handle_parent_process(&input_fd, pipes, pid);
		cmd = cmd->next;
	}
}


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
