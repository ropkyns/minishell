/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:11:25 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/20 14:15:40 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_key(char *str)
{
	if (ft_strchr(str, '='))
		return (ft_strndup(str, ft_strchr(str, '=') - str));
	return (ft_strdup(str));
}

char	*extract_value(char *str)
{
	if (ft_strchr(str, '='))
		return (ft_strdup(ft_strchr(str, '=') + 1));
	return (ft_strdup(""));
}

bool	is_valid_value(char *key, char *value)
{
	if (ft_strstr(value, key) != NULL && value[0] == '$')
		return (false);
	return (true);
}

char	*build_full_str(char *key, char *value)
{
	char	*full_str;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	full_str = malloc(key_len + 1 + value_len + 1);
	if (!full_str)
		return (NULL);
	ft_memcpy(full_str, key, key_len);
	full_str[key_len] = '=';
	ft_memcpy(full_str + key_len + 1, value, value_len);
	full_str[key_len + 1 + value_len] = '\0';
	return (full_str);
}

bool	update_or_add_env(t_env **env, char *key, char *value, char *full_str)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			free(current->value);
			free(current->str);
			current->value = value;
			current->str = full_str;
			return (true);
		}
		prev = current;
		current = current->next;
	}
	if (add_node_env(env, full_str))
		return (true);
	return (false);
}
