/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:35 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/25 17:11:29 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_flag_n(char *line)
{
	int	i;

	i = 0;
	if (line[i] && line[i] == '-' && line[i + 1] == 'n')
	{
		++i;
		while (line[i] && line[i] == 'n')
			i++;
		if (line[i] == '\0')
			return (1);
	}
	return (0);
}

static void	print_echo(int count, int i, bool *n_flag, char **args)
{
	while (i < count && check_flag_n(args[i]))
	{
		++i;
		*n_flag = false;
	}
	while (i < count)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (i != count - 1)
			write(1, " ", 1);
		++i;
	}
	if (*n_flag)
		write(1, "\n", 1);
}

int	ft_echo(char **args)
{
	int		count;
	int		i;
	bool	n_flag;

	count = 0;
	i = 1;
	n_flag = true;
	while (args[count])
		++count;
	print_echo(count, i, &n_flag, args);
	return (0);
}
