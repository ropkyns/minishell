/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:50:14 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/20 15:21:53 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static bool	handle_builtin_command(t_global *glob, t_cmd *cmd)
// {
// 	if (is_simple_command(glob->token_list) && is_builtins(cmd->cmd_args[0]))
// 	{
// 		return (launch_builtin(glob, cmd));
// 	}
// 	return (false);
// }

// static bool	is_command_absolute_or_relative(t_cmd *cmd, t_global *glob,
// 		char **path_name)
// {
// 	if (cmd->cmd_args[0][0] == '/' || cmd->cmd_args[0][0] == '.')
// 	{
// 		if (is_directory(cmd->cmd_args[0]))
// 		{
// 			printf("bash: %s: Is a directory\n", cmd->cmd_args[0]);
// 			glob->exit_value = 126;
// 			return (false);
// 		}
// 		if (access(cmd->cmd_args[0], X_OK) == 0)
// 		{
// 			*path_name = ft_strdup(cmd->cmd_args[0]);
// 			return (true);
// 		}
// 		else
// 		{
// 			glob->exit_value = 127;
// 			printf("bash: %s: command not found\n", cmd->cmd_args[0]);
// 			return (false);
// 		}
// 	}
// 	return (false);
// }

static void	exit_value(int flag, t_global *glob, t_cmd *cmd)
{
	if (flag == E_ONE)
	{
		glob->exit_value = 127;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	else if (flag == E_ONE2)
	{
		glob->exit_value = 127;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (flag == E_TWO)
	{
		glob->exit_value = 126;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
}

// static void	handle_command_execution(t_cmd *cmd, char *path_name,
// 		t_global *glob, t_env **env)
// {
// 	execute_choice(cmd, path_name, glob, env);
// 	free(path_name);
// }

/*
* La premiere partie de l'exec, ici on va regarder si il n'y a qu'une
seule commande ou plusieurs avec pipes.

1- > si il n'y en a qu'une on verifie si c'est un builtin,
si c'est le cas on lance le builtin et bravo.

2- > On va envoyer notre nom de cmd dans find executable,
qui va d'abord creer le path avec un strcpy/strcat, pour ensuite
voir si le path est correct et que la cmd existe et est executable.

3- > une seule commande mais pas un builtin, alors dans ce cas
on va l'envoyer dans execute_command -> execute_simple
qui va grosso modo juste execve avec le path qu'on a
cree avant dans un child process pour que cela
ne kill pas notre programme.

4-
Sinon, on va dans execute_piped car il y a plusieurs commandes (et donc pipe)
et la c'est la galere on se revoie la bas ciao (j'aurais du faire pipex)
*/
// bool	get_cmd(t_cmd *cmd, t_global **glob, t_env **env)
// {
// 	t_global	*temp;
// 	char		*path_name;

// 	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0] || !glob || !*glob)
// 		return (false);
// 	temp = *glob;
// 	if (handle_builtin_command(*glob, cmd))
// 		return (true);
// 	if (cmd->cmd_args[0][0] == '/' || cmd->cmd_args[0][0] == '.')
// 	{
// 		if (is_directory(cmd->cmd_args[0]))
// 		{
// 			printf("bash: %s: Is a directory\n", cmd->cmd_args[0]);
// 			(*glob)->exit_value = 126;
// 			return (false);
// 		}
// 		if (access(cmd->cmd_args[0], X_OK) == 0)
// 		{
// 			path_name = ft_strdup(cmd->cmd_args[0]);
// 			return (true);
// 		}
// 		else
// 		{
// 			(*glob)->exit_value = 127;
// 			printf("bash: %s: command not found\n", cmd->cmd_args[0]);
// 			return (false);
// 		}
// 	}
// 	return (false);
// 	if (check_executable_in_path(*glob, cmd, &path_name))
// 	{
// 		handle_command_execution(cmd, path_name, *glob, env);
// 		return (true);
// 	}
// 	return (false);
// }

bool	get_cmd(t_cmd *cmd, t_global **glob, t_env **env)
{
	t_global	*temp;
	char		*path_name;

	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0] || !glob || !*glob)
		return (false);
	temp = *glob;
	if (is_simple_command(temp->token_list) && is_builtins(cmd->cmd_args[0]))
		return (launch_builtin(*glob, cmd));
	if (cmd->cmd_args[0][0] == '/' || cmd->cmd_args[0][0] == '.')
	{
		if (is_directory(cmd->cmd_args[0]))
			return (exit_value(E_TWO, *glob, cmd), false);
		if (access(cmd->cmd_args[0], X_OK) == 0)
		{
			path_name = ft_strdup(cmd->cmd_args[0]);
			return (process(cmd, path_name, temp, env), free(path_name), true);
		}
		else
			return (exit_value(E_ONE, *glob, cmd), false);
	}
	path_name = find_executable(temp->path, cmd->cmd_args[0]);
	if (path_name)
		return (process(cmd, path_name, temp, env), free(path_name), true);
	else
		return (exit_value(E_ONE2, *glob, cmd), false);
}
