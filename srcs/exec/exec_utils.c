/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:36:23 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/12 10:23:53 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * J'avais plus de place dans ma fonction j'ai du decouper ca ca fait pitie
 */
bool	check_allocation(void *ptr)
{
	if (!ptr)
	{
		printf("malloc error");
		return (false);
	}
	return (true);
}

/*
 * Regarde si il y a un pipe, si oui alors y a une autre commande
 */
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

/*
* On prend la liste chainee des env et on va en faire un char **
(en copie bien sur)
*/
char	**make_env_tab(t_env *env)
{
	t_env	*current_env;
	int		i;
	char	**env_array;

	current_env = env;
	i = 0;
	env_array = NULL;
	env_array = malloc(sizeof(char *) * (len_env(env) + 1));
	if (!env_array)
		return (NULL);
	while (current_env)
	{
		env_array[i] = current_env->str;
		current_env = current_env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

/*
 * Return la value d'une variable env
 */
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

/*
* Gere ces builtins dans le parent et pas dans un child process
vu que ca touche aux env :-)
*/
int	handle_builtin_parent(t_cmd **cmd, t_global *glob, int *input_fd,
		int *pipes)
{
	if (is_builtins((*cmd)->cmd_args[0]) && (!ft_strcmp((*cmd)->cmd_args[0],
				"unset")))
	{
		launch_builtin(glob, *cmd);
		if ((*cmd)->next)
		{
			*input_fd = pipes[0];
			close(pipes[1]);
		}
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}
