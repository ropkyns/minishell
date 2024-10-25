/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:03:52 by mjameau           #+#    #+#             */
/*   Updated: 2024/10/23 17:51:18 by paulmart         ###   ########.fr       */
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
# include <sys/wait.h>
# include <term.h>
# include <termios.h>

# define FAIL 1
# define SUCCESS 0

typedef enum e_token
{
	INPUT = 1,
	OUTPUT = 2,
	HEREDOC = 3,
	APPEND = 4,
	CMD = 5,
	ARG = 6,
	PIPE = 7,
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
	char				**cmd_args;
	int					infile;
	int					outfile;
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

// BUILTIN
int						ft_pwd(void);
int						ft_cd(t_global *test, char **args);
int						ft_export(t_env **env, char **str);
bool	export_value(t_env **env, char *str);
int						ft_unset(t_env **env, char **args);
void					ft_exit(char **args, t_global *glob);
int						ft_echo(char **args);
int	ft_env(t_env *env);

// UTILS
bool					is_space(char c);
bool					syntax_is_correct(char *lexer_tokens[]);
bool					check_allocation(void *ptr);
bool					is_simple_command(t_structok *token_list);
void	sort_array(char **arr, int len);
size_t	len_env(t_env *env);
void ft_swap_str_tab(int i, int j, char **arr);

// SYNTAX
bool					handle_quotes(t_global *data, char *command);
bool					is_last_pipe(t_structok **tok_list, t_global *glob);
bool					is_first_pipe(t_structok **tok_list, t_global *glob);
bool					is_last_op(t_structok **tok_list, t_global *glob);
bool					is_op_before_pipe(t_structok **tok_list,
							t_global *glob);
void					print_error_syntax(char *value);
bool					is_op_after_op(t_structok **tok_list, t_global *glob);
void					print_error_syntax(char *value);
void					check_dollar_sign(t_structok **toklist, t_env *env, t_global *glob);
bool					check_syntax(t_global *glob, t_structok **token_list);

// TOKENS
int						add_token(t_structok **token_list, char *s, int type);
bool					add_operator_token(t_structok **head, char **command);
void					free_tok(t_structok **token_list);
bool					do_list_token(t_structok **head, char *command);
bool					add_cmd_arg(t_structok **head, char **command);
void					print_token(t_structok *token_list);

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
void					free_env(t_env *a);

// CMD
void					init_cmd(t_cmd **cmd, t_structok **tok_list,
							t_global *glob);
t_cmd					*find_last_node_cmd(t_cmd *cmd);
void					handle_input_output(t_cmd *last, t_structok *toklist,
							t_global *glob);
char					**args_tab(t_structok *toklist, t_global *glob,
							t_structok *head);

// PATH
char					**init_path(char **env);

// SIGNAL
void					handle_signal(void);
void					handle_c(int sig);

// EXEC
void	get_builtins(int save_stdout, t_cmd *cmd, t_global *glob);
bool					is_builtins(char *cmd);
bool	get_cmd(t_cmd *cmd, t_global **glob, t_env **env);
void					execute_simple(t_cmd *cmd, char *path_name,
							t_env **env);
void					execute_piped(t_cmd *cmd, t_env **env, t_global *glob);

void					handle_redir(t_cmd *cmd);
char	**make_env_tab(t_env *env);
char					*get_command_path(char *cmd, t_env *env_list);
char					*build_path(char *dir, char *cmd);
char					*get_env_value(t_env *env_list, const char *name);
bool	launch_builtin(t_global *glob, t_cmd *cmd);

#endif