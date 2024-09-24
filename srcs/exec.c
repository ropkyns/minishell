/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:06:59 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/24 14:42:53 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../lib/libft.h"

char	**init_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	printf("%s\n", env[i]);
	path = ft_split(env[i] + 5, ':');
	if (!path)
		return (NULL);
	return (path);
}
