/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:50:14 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/23 15:50:01 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**make_env_tab(t_env *env)
{
	t_env	*current_env;
	int		count;
	char	**env_array;

	current_env = env;
	count = 0;
	while (current_env)
	{
		count++;
		current_env = current_env->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!check_allocation(env_array))
		return (NULL);
	current_env = env;
	count = 0;
	while (current_env)
	{
		env_array[count] = current_env->str;
		current_env = current_env->next;
		count++;
	}
	env_array[count] = NULL;
	return (env_array);
}

static char	*find_executable(char **path_list, char *cmd_name)
{
	int		i;
	char	*path_name;

	i = 0;
	while (path_list[i])
	{
		path_name = build_path(path_list[i], cmd_name);
		if (path_name && access(path_name, X_OK) == 0)
			return (path_name);
		free(path_name);
		i++;
	}
	return (NULL);
}

static void	execute_command(t_cmd *cmd, char *path_name, t_global *glob,
		t_env **env)
{
	if (is_simple_command(glob->token_list))
		execute_simple(cmd, path_name, env);
	else
		execute_piped(cmd, env, glob);
}

// bool	get_cmd(t_cmd *cmd, t_global **glob, t_env **env)
// {
// 	t_global	*temp;
// 	char		*path_name;

// 	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0] || !glob || !*glob)
// 		return (false);
// 	temp = *glob;
// 	if (is_simple_command(temp->token_list) && is_builtins(cmd->cmd_args[0]))
// 		return (launch_builtin(*glob, cmd));
// 	if (!temp->path)
// 		return(false) ;
// 	path_name = find_executable(temp->path, cmd->cmd_args[0]);
// 	if (path_name)
// 	{
// 		execute_command(cmd, path_name, temp, env);
// 		free(path_name);
// 		return (false);
// 	}
// 	printf("bash: command not found: %s\n", cmd->cmd_args[0]);
// 	return(false);
// }

bool	get_cmd(t_cmd *cmd, t_global **glob, t_env **env)
{
	t_global	*temp;
	char		*path_name;

	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0] || !glob || !*glob)
		return (false);
	temp = *glob;
	if (is_simple_command(temp->token_list)) 
	{
		if (is_builtins(cmd->cmd_args[0]))
			return (launch_builtin(*glob, cmd));
		path_name = find_executable(temp->path, cmd->cmd_args[0]);
		if (path_name)
		{
			execute_command(cmd, path_name, temp, env);
			free(path_name);
			return (true);
		}
		else
			return (printf("bash: command not found: %s\n", cmd->cmd_args[0]), false);
	}
	execute_piped(cmd, env, *glob);
	return (true);
}



