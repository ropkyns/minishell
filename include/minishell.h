/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:03:52 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/18 13:17:17 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <linux/limits.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <term.h>
# include <termios.h>

# define FAIL 1
# define SUCCESS 0

typedef enum e_token
{
	CMD,
	PIPE,
	ARG,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}			t_token;

typedef struct s_structok
{
	char			*value;
	int				token;
	struct s_token	*next;
}				t_structok;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_global
{
	char			*line;
	t_env			*env;
}					t_global;

int					ft_pwd(void);
int					ft_cd(t_global *test, char *args);
bool				syntax_is_correct(char *lexer_tokens[]);

#endif