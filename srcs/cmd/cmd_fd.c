/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:02:08 by paulmart          #+#    #+#             */
/*   Updated: 2024/11/20 16:44:11 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Gere les redirections > et < et << et >>
 */
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
			ft_putstr_fd(": No such file or directory\n", 2);
			error_exit(NULL, glob);
		}
	}
	else if (toklist->type == OUTPUT)
		last->outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (toklist->type == APPEND)
		last->outfile = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (toklist->type == HEREDOC)
		last->infile = fd_heredoc(filename, glob);
}

static void	write_heredoc(int fd, char *str)
{
	if (fd == 2)
	{
		write(2, "warning: here-document delimited by end-of-file ", 48);
		write(2, "(wanted '", 9);
		write(2, str, ft_strlen(str));
		write(2, "')\n", 3);
	}
	else
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}

static bool	read_heredoc(int fd, char *end_word, t_env *env, t_global *glob)
{
	char				*buf;
	struct sigaction	sa;

	sa.sa_handler = heredoc_signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (false);
	while (1)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf)
		{
			write_heredoc(2, end_word);
			break ;
		}
		if (!replace_dollar(&buf, env, glob))
			error_exit(NULL, glob);
		if (!ft_strcmp(end_word, buf))
			break ;
		write_heredoc(fd, buf);
		free(buf);
	}
	return (close(fd), true);
}

static int	wrong_pid(int *fd, pid_t pid, int status)
{
	close(*fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		*fd = open(".heredoc.tmp", O_RDONLY);
		if (fd > 0)
			unlink(".heredoc.tmp");
	}
	else
		*fd = -1;
	return (*fd);
}

int	fd_heredoc(char *filename, t_global *glob)
{
	int		fd;
	pid_t	pid;
	int		status;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (close(fd), -1);
	else if (pid == 0)
	{
		if (!read_heredoc(fd, filename, glob->env, glob))
		{
			close(fd);
			unlink(".heredoc.tmp");
			exit(1);
		}
		close(fd);
		exit(0);
	}
	else
		wrong_pid(&fd, pid, status);
	unlink(".heredoc.tmp");
	return (fd);
}
