/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:03:52 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/27 10:38:20 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
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
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_cmd
{
	char				*cmd;
	int infile;  // fd
	int outfile; // fd
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_global
{
	char				*line;
	char				**path;
	t_env				*env;
	t_structok			*token_list;
	int					exit_value;
	t_cmd				*cmd;
}						t_global;

// ERROR
void					free_env(t_env *env);
void					error_exit(char *str, t_global *glob);
void					free_cmd(t_cmd *cmd);
void					free_path(char **path);

// COMMANDS
int						ft_pwd(void);
int						ft_cd(t_global *test, char *args);
int						ft_export(t_env **env, char **str);
bool					export_value(t_env **env, char *str);

// UTILS
bool					is_space(char c);
bool					syntax_is_correct(char *lexer_tokens[]);

// PARSING
bool						handle_quotes(t_global *data, char *command);
bool					is_last_pipe(t_structok **tok_list);
bool					is_first_pipe(t_structok **tok_list);

// TOKENS
// int					new_token(t_structok **new, char *s, t_token type);
int						add_token(t_structok **token_list, char *s, int type);
bool					add_operator_token(t_structok **head, char **command);
void					free_tok(t_structok **token_list);
bool					do_list_token(t_structok **head, char *command);
bool					add_cmd_arg(t_structok **head, char **command);

// UTILS TOKEN
int						len_cmd(char *command, int *quote);
int						is_special(char *token);
void					get_words_to_token(char *command, int len, char *str,
							int i);
void					add_first_token(t_structok **token_list,
							t_structok *new);

// ENV
void					init_env(t_env **list, char **env);
bool					add_node_env(t_env **env, char *value);
void					print_env(t_env *env);
void					free_env(t_env *a);

// CMD
void					init_cmd(t_cmd **cmd, t_structok **tok_list);

// PATH
char					**init_path(char **env);

// SIGNAL
void					handle_signal(void);
void					handle_c(int sig);

#endif