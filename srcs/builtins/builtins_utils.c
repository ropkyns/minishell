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

void	get_builtins(int save_stdout, t_cmd *cmd, t_global *glob)
{
	if (ft_strcmp(cmd->cmd_args[0], "echo") == 0)
		glob->exit_value = ft_echo(cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "cd") == 0)
		glob->exit_value = ft_cd(glob, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "export") == 0)
		glob->exit_value = ft_export(&glob->env, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "unset") == 0)
		glob->exit_value = ft_unset(&glob->env, cmd->cmd_args);
	else if (ft_strcmp(cmd->cmd_args[0], "pwd") == 0)
		glob->exit_value = ft_pwd();
	else if (ft_strcmp(cmd->cmd_args[0], "env") == 0)
		ft_env(glob->env);
	else if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
	{
		if(cmd->outfile >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		ft_exit(cmd->cmd_args, glob);
	}
}

bool	launch_builtin(t_global *glob, t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->outfile, 1);
	}
	get_builtins(save_stdout, cmd, glob);
	if (cmd->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close (save_stdout);
	}
	return (true);
}

void ft_swap_str_arr(int i, int j, char **arr)
{
    char *temp;

    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void sort_array(char **arr, int len)
{
    int i;
    int j;
    int diff;

    i = 0;
    while (i < len)
    {
        j = i + 1;
        while (j < len)
        {
            diff = ft_strncmp(arr[i], arr[j], __INT_MAX__);
            if (diff > 0)
            {
                ft_swap_str_arr(i, j, arr);
                continue;
            }
            j++;
        }
        i++;
    }
}
