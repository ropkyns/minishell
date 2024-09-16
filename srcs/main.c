/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palu <palu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:29:04 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/16 21:45:20 by palu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



int	main(void)
{
	char	*rl;
	char	**parth;

	isatty(1);
	while (1)
	{
		rl = readline("minishell > ");
		parth = ft_split(rl, ' ');
		if (!parth)
			return (NULL); //TODO cas d'erreur
		add_history(rl);
	}
	return (1);
}
