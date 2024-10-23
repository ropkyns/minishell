/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:36:23 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/23 15:55:56 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_allocation(void *ptr)
{
	if (!ptr)
	{
		printf("malloc error");
		return (false);
	}
	return (true);
}

bool	is_simple_command(t_structok *token_list)
{
	t_structok	*temp;

	if (!token_list)
		return (true);
	temp = token_list;
	while (temp->next != token_list && token_list->next)
	{
		if (temp->type == PIPE)
			return (false);
		temp = temp->next;
	}
	return (true);
}

char	*build_path(char *dir, char *cmd)
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

char	*get_env_value(t_env *env_list, const char *name)
{
	while (env_list)
	{
		if (strcmp(env_list->name, name) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
