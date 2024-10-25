/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:28:26 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/25 17:33:57 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	atoi_exit(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					is_neg;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	is_neg = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			is_neg = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((is_neg == -1 && (ret - 1) > LONG_MAX)
			|| (is_neg == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * is_neg) % 256));
}

void	ft_exit(char **args, t_global *glob)
{
	int	error;

	error = 0;
	if (args[1])
	{
		glob->exit_value = atoi_exit(args[1], &error);
		if (error)
		{
			glob->exit_value = 2;
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			error_exit("", glob);
		}
	}
	if (args[1] && args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		glob->exit_value = 1;
		return ;
	}
	if (!args[1])
		error_exit(NULL, glob);
	error_exit(NULL, glob);
}
