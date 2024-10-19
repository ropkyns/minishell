/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:02 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/15 14:54:28 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_builtins(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp("pwd", cmd) || !ft_strcmp("echo", cmd) || !ft_strcmp("exit",
			cmd) || !ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd)
		|| !ft_strcmp("export", cmd) || !ft_strcmp("cd", cmd))
		return (true);
	return (false);
}

void	get_builtins(t_cmd *cmd, t_env **env, t_global **glob)
{
	if (ft_strcmp(cmd->cmd_args[0], "echo") == 0)
		ft_echo(cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "cd") == 0)
		ft_cd(*glob, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
		ft_exit(cmd->cmd_args, *glob);
	else if (ft_strcmp(cmd->cmd_args[0], "export") == 0)
		ft_export(env, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "unset") == 0)
		ft_unset(env, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd_args[0], "env") == 0)
		ft_env(*env);
}
