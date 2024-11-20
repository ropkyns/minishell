/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:14:53 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/20 15:19:15 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	handle_in_out(t_cmd *cmd)
{
	if (cmd->infile >= 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			perror("dup2 infile");
			exit(1);
		}
		close(cmd->infile);
		if (cmd->outfile >= 0)
		{
			if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			{
				perror("dup2 outfile");
				exit(1);
			}
			close(cmd->outfile);
		}
	}
}

static char	**create_env_array(t_env **env)
{
	char	**env_array;

	env_array = make_env_tab(*env);
	if (!env_array)
	{
		exit(1);
	}
	return (env_array);
}

static void	execute_with_execve(char *path_name, t_cmd *cmd, char **env_array)
{
	if (execve(path_name, cmd->cmd_args, env_array) == -1)
	{
		free(env_array);
		exit(1);
	}
	free(env_array);
	exit(0);
}

void	handle_parent_process2(t_cmd *cmd)
{
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
}

/*
* Execve dans un child process si il n'y a pas de pipe
(une seule commande en gros), on gere aussi les redirections
car il peut y avoir un heredoc
*/
void	execute_simple(t_cmd *cmd, char *path_name, t_env **env, t_global *glob)
{
	pid_t	pid;
	char	**env_array;
	char	*executable;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		handle_in_out(cmd);
		env_array = create_env_array(env);
		executable = get_command_path(cmd->cmd_args[0], *env);
		if (!executable)
		{
			free(env_array);
			printf("bash: %s: No such file or directory\n", cmd->cmd_args[0]);
			glob->exit_value = 127;
			exit(127);
		}
		execute_with_execve(path_name, cmd, env_array);
		free(executable);
	}
	else
		simple_exec_fail_pid(glob, pid, cmd);
}
