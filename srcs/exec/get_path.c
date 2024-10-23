/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:02 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/23 15:51:52 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_absolute_relative_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*get_next_dir(char **start, char *end)
{
	char	*dir;

	if (end)
	{
		dir = malloc(end - *start + 1);
		if (!dir)
			return (NULL);
		ft_strlcpy(dir, *start, end - *start + 1);
		*start = end + 1;
	}
	else
	{
		dir = ft_strdup(*start);
		*start = NULL;
	}
	return (dir);
}

static char	*search_command_in_path(char *path_var, char *cmd)
{
	char	*start;
	char	*end;
	char	*dir;
	char	*path_name;

	start = path_var;
	while (start)
	{
		end = ft_strchr(start, ':');
		dir = get_next_dir(&start, end);
		if (!dir)
			return (NULL);
		path_name = build_path(dir, cmd);
		free(dir);
		if (access(path_name, X_OK) == 0)
			return (path_name);
		free(path_name);
	}
	return (NULL);
}

char	*get_command_path(char *cmd, t_env *env_list)
{
	char	*path_var;

	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (handle_absolute_relative_path(cmd));
	path_var = get_env_value(env_list, "PATH");
	if (!path_var)
		return (NULL);
	return (search_command_in_path(path_var, cmd));
}
