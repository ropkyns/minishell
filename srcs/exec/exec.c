/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:50:14 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/21 15:40:28 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*build_path(char *dir, char *cmd)
{
	int		len_path;
	int		cmd_len;
	char	*path_name;

	len_path = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	path_name = malloc(sizeof(char) * (len_path + cmd_len + 2));
	if (!check_allocation(path_name))
		return (NULL);
	ft_strlcpy(path_name, dir, len_path + 1);
	ft_strcat(path_name, "/");
	ft_strcat(path_name, cmd);
	return (path_name);
}

char	**make_env_tab(t_env **env)
{
	t_env	*current_env;
	int		count;
	char	**env_array;

	current_env = *env;
	count = 0;
	while (current_env)
	{
		count++;
		current_env = current_env->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!check_allocation(env_array))
		return (NULL);
	current_env = *env;
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

// static bool	execute_command(t_cmd *cmd, char *path_name, char **env_array)
// {
// 	if (execve(path_name, cmd->cmd_args, env_array) == -1)
// 	{
// 		printf("error in execve");
// 		return (false);
// 	}
// 	return (true);
// }

// static bool	try_execute(t_cmd *cmd, char *path_name, t_env **env)
// {
// 	char	**env_array;

// 	env_array = make_env_tab(env);
// 	if (!env_array)
// 		return (false);
// 	if (execute_command(cmd, path_name, env_array))
// 	{
// 		free(env_array);
// 		return (true);
// 	}
// 	free(env_array);
// 	return (false);
// }

void	get_cmd(t_cmd *cmd, t_global **glob, t_env **env)
{
	int			i;
	t_global	*temp;
	char		*path_name;

	i = 0;
	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[0] || !glob || !*glob)
		return ;
	temp = *glob;
	if (!temp->path)
		return ;
	while (temp->path[i])
	{
		path_name = build_path(temp->path[i], cmd->cmd_args[0]);
		if (!path_name)
			return ;
		if (access(path_name, X_OK) == 0)
		{
			if (is_simple_command((*glob)->token_list))
				execute_simple(cmd, path_name, env);
			else if (!is_simple_command((*glob)->token_list))
				execute_piped(cmd, env, path_name, *glob);
			return (free(path_name));
		}
		free(path_name);
		i++;
	}
	printf("bash: command not found: %s\n", cmd->cmd_args[0]);
}

// int	main(int argc, t_cmd *cmd, char **envp)
// {
// 	t_global *glob = malloc(sizeof(t_global));
// 	if (!glob)
// 	{
// 		perror("Erreur allocation mémoire pour glob");
// 		return (1);
// 	}
// 	char *paths[] = {"/bin", "/usr/bin", NULL};
// 	glob->path = paths;
// 	t_env *env_list = NULL;
// 	init_env(&env_list, envp);
// 	if (argc > 1)
// 		get_cmd(argv + 1, &glob, &env_list);
// 	else
// 		printf("Usage: %s <command>\n", argv[0]);
// 	t_env *current = env_list;
// 	while (current)
// 	{
// 		t_env *next = current->next;
// 		free(current->str);
// 		free(current);
// 		current = next;
// 	}
// 	return (0);
// }