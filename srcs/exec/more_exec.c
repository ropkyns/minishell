/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:02 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/04 18:11:32 by mjameau          ###   ########.fr       */
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

void	get_builtins(char **argv, t_env **env, t_global **glob)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(*glob, argv);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit(argv, *glob);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(env, argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(env, argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(*env);
}