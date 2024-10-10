/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:25:10 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/10 10:39:46 by mjameau          ###   ########.fr       */
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
void	execute_simple(t_cmd *cmd, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0) // child
	{
		handle_redir(cmd);
		execve(cmd->cmd, cmd->cmd_args, env);
		printf("execve error\n");
		exit(1);
	}
	else // parent
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

	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipes) == -1)
				error_exit("pipe error", glob);
		pid = fork();
		if (pid < 0)
			error_exit("fork error", glob);
		if (pid == 0)
		{
			if (cmd->infile != STDIN_FILENO)
			{
				if (dup2(cmd->infile, STDIN_FILENO) == -1)
					error_exit("dup2 infile error", glob);
				close(cmd->infile);
			}
			if (cmd->next)
			{
				if (dup2(pipes[1], STDOUT_FILENO) == -1)
					error_exit("dup2 pipe[1] error", glob);
				close(pipes[0]);
			}
			handle_redir(cmd);
			execve(cmd->cmd, cmd->cmd_args, env);
			error_exit("execve error", glob);
		}
		else
		{
			if (cmd->next)
				close(pipes[1]);
			cmd->infile = pipes[0];
			waitpid(pid, NULL, 0);
			cmd = cmd->next;
		}
	}
}

void	handle_redir(t_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			perror("dup2 infile error");
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			perror("dup2 outfile error");
		close(cmd->outfile);
	}
}
