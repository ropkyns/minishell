/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:16:34 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/12 10:20:15 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_env_var(t_env **env, char *name, char *value)
{
	size_t	name_len;
	size_t	value_len;
	char	*env_var;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	env_var = malloc(name_len + value_len + 2);
	if (!env_var)
		return ;
	ft_strncpy(env_var, name, name_len);
	env_var[name_len] = '=';
	ft_strncpy(env_var + name_len + 1, value, value_len + 1);
	add_node_env(env, env_var);
	free(env_var);
}
