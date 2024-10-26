/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:02:08 by paulmart          #+#    #+#             */
/*   Updated: 2024/10/26 18:14:59 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* PETIT PB HEREDOC AVEC ERREUR DE EOF NE DISPLAY PAS LE PROMPT MINISHELL ENSUITE */

void	handle_input_output(t_cmd *last, t_structok *toklist, t_global *glob)
{
	char	*filename;

	filename = toklist->next->value;
	if (last->infile >= 0)
		close(last->infile);
	if (last->outfile >= 0)
		close(last->outfile);
	if (toklist->type == INPUT)
	{
		last->infile = open(filename, O_RDONLY, 0644);
		if (last->infile == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(toklist->next->value, 2);
			ft_putstr_fd(": No such file or directory", 2);
			error_exit(NULL, glob);
		}
	}
	else if (toklist->type == OUTPUT)
		last->outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (toklist->type == APPEND)
		last->outfile = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (toklist->type == HEREDOC)
		last->infile = fd_heredoc(filename);
}

static bool	read_heredoc(int fd, char *end_word)
{
	char	*buf;

	while (1)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf)
		{
			write(2, "warning: here-document delimited by end-of-file ", 48);
			write(2, "(wanted '", 9);
			write(2, end_word, ft_strlen(end_word));
			write(2, "')\n", 3	);
			break ;
		}
		if (!ft_strncmp(end_word, buf, INT_MAX))
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
	close(fd);
	return (true);
}

int	fd_heredoc(char *filename)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_heredoc(fd, filename))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}
