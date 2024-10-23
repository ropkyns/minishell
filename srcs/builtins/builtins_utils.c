/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:54:23 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/23 15:54:38 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:02 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/21 14:45:13 by mjameau          ###   ########.fr       */
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
		(*glob)->exit_value = ft_echo(cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "cd") == 0)
		(*glob)->exit_value = ft_cd(*glob, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
		ft_exit(cmd->cmd_args, *glob);
	else if (ft_strcmp(cmd->cmd_args[0], "export") == 0)
		(*glob)->exit_value = ft_export(env, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "unset") == 0)
		(*glob)->exit_value = ft_unset(env, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "pwd") == 0)
		(*glob)->exit_value = ft_pwd();
	else if (ft_strcmp(cmd->cmd_args[0], "env") == 0)
		ft_env(*env);
}
