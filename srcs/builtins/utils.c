/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:44:03 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/25 15:44:39 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(t_env *env)
{
	while (env->next)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
