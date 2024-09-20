/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:03:52 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/20 15:50:32 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <linux/limits.h>
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
}						t_token;

typedef struct s_structok
{
	char				*value;
	struct s_structok	*next;
	struct s_structok	*prev;
	t_token				type;
}						t_structok;

typedef struct s_env
{
	char				*str;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_global
{
	char				*line;
	t_env				*env;
	t_structok			*token_list;
}						t_global;

// COMMANDS
int						ft_pwd(void);
int						ft_cd(t_global *test, char *args);

// UTILS
bool					is_space(char c);
bool					syntax_is_correct(char *lexer_tokens[]);

// TOKENS
int						new_token(t_structok **new, char *s, t_token type);
int						add_token(t_structok **token_list, char *s, int type);
bool					add_operator_token(t_structok **head, char *command);
void					free_tok(t_structok **token_list);
bool					do_list_token(t_structok **head, char *command);
bool					add_cmd_arg(t_structok **head, char **command);

// UTILS TOKEN
int						len_cmd(char *command, int *quote);
int						is_special(char *token);
void					get_words_to_token(char *command, int len, char *str,
							int i);

// ENV
t_env					*init_env(char **env);

#endif