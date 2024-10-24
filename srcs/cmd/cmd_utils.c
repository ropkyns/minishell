/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:11:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/23 15:24:33 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*find_last_node_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

void	handle_input_output(t_cmd *last, t_structok *toklist, t_global *glob)
{
	if (toklist->type == INPUT)
	{
		last->infile = open(toklist->next->value, 0);
		if (last->infile == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(toklist->next->value, 2);
			ft_putstr_fd(": No such file or directory", 2);
			error_exit(NULL, glob);
		}
	}
	else if (toklist->type == OUTPUT)
		last->outfile = open(toklist->next->value, O_CREAT, S_IRWXU);
}

static int	count_args(t_structok *toklist, t_structok *head)
{
	int			count;
	t_structok	*tmp;

	count = 0;
	tmp = toklist;
	while (tmp->next != head && (tmp->next->type == ARG
			|| tmp->next->type == CMD))
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	fill_args_array(char **ret, t_structok *toklist, t_global *glob,
		t_structok *head)
{
	int	i;

	i = 0;
	if (toklist->type == CMD)
	{
		ret[i] = ft_strdup(toklist->value);
		if (!ret[i])
			error_exit("Allocation failed", glob);
		i++;
	}
	while (toklist->next != head && (toklist->next->type == ARG
			|| toklist->next->type == CMD))
	{
		if (toklist->next->value)
		{
			ret[i] = ft_strdup(toklist->next->value);
			if (!ret[i])
				error_exit("Allocation failed", glob);
		}
		else
			ret[i] = NULL;
		i++;
		toklist = toklist->next;
	}
	ret[i] = NULL;
}

char	**args_tab(t_structok *toklist, t_global *glob, t_structok *head)
{
	int		arg_count;
	char	**ret;

	arg_count = count_args(toklist, head);
	ret = malloc(sizeof(char *) * (arg_count + 2));
	if (!ret)
		error_exit("Allocation failed", glob);
	fill_args_array(ret, toklist, glob, head);
	return (ret);
}
