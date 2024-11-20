# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 12:03:49 by mjameau           #+#    #+#              #
#    Updated: 2024/11/20 14:14:33 by mjameau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


RESET			= "\033[0m"
BLACK    		= "\033[30m"
RED      		= "\033[31m"
GREEN    		= "\033[32m"
YELLOW   		= "\033[33m"
BLUE     		= "\033[34m"
MAGENTA  		= "\033[35m"
CYAN     		= "\033[36m"
WHITE    		= "\033[37m"

SRC		=	main.c builtins/cd.c builtins/export.c builtins/echo.c builtins/pwd.c builtins/exit.c \
			builtins/unset.c exec/exec_utils.c exec/exec.c exec/get_path.c exec/child_process.c builtins/ft_env.c \
			cmd/cmd_utils.c env.c error/free_exit.c tokens/free_tokens.c tokens/create_token.c \
			tokens/utils_token.c cmd/cmd.c path.c builtins/builtins_utils.c signal/handle_signal.c \
			parsing/syntax.c parsing/more_syntax.c parsing/even_more_syntax.c cmd/cmd_fd.c parsing/parsing_utils.c\
			exec/execute_one_cmd.c exec/exec_utils2.c env_utils.c builtins/export_utils.c

NAME	=	minishell

FLAGS	=	-Wall -Wextra -Werror -lreadline lib/libft.a -std=c99

RM		= rm -f

LIB_DIR	=	lib/
LIBFT 	=	libft.a

SRCS 	= $(addprefix ./srcs/, $(SRC))
OBJS	=	$(SRCS:.c=.o)

HEADER	=	minishell.h

all: $(LIB_DIR) $(LIBFT) $(NAME)

%.o:	%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	@echo $(RED)"C"$(YELLOW)"o"$(GREEN)"m"$(CYAN)"p"$(BLUE)"i"$(MAGENTA)"l"$(RED)"i"$(YELLOW)"n"$(GREEN)"g" $(CYAN)"m"$(BLUE)"i"$(MAGENTA)"n"$(RED)"i"$(YELLOW)"s"$(GREEN)"h"$(CYAN)"e"$(BLUE)"l"$(MAGENTA)"l"$(RED)"."$(YELLOW)"."$(GREEN)"." $(RESET)
	@cc $(OBJS) $(FLAGS) -o $(NAME)
	@echo $(RED)"D"$(YELLOW)"o"$(GREEN)"n"$(CYAN)"e"$(BLUE)"!"$(MAGENTA)"!" $(RED)"💫" $(RESET)

$(LIBFT):
	@echo $(RED)"M"$(YELLOW)"a"$(GREEN)"k"$(CYAN)"i"$(BLUE)"n"$(MAGENTA)"g" $(RED)"l"$(YELLOW)"i"$(GREEN)"b"$(CYAN)"f"$(BLUE)"t"$(MAGENTA)"."$(RED)"."$(YELLOW)"." $(RESET)
	@make --no-print-directory -C $(LIB_DIR)
	@echo $(RED)"D"$(YELLOW)"o"$(GREEN)"n"$(CYAN)"e"$(BLUE)"!"$(MAGENTA)"!" $(RED)"✨" $(RESET)


clean:
	@echo $(RED)"C"$(YELLOW)"l"$(GREEN)"e"$(CYAN)"a"$(BLUE)"n"$(MAGENTA)"i"$(RED)"n"$(YELLOW)"g" $(GREEN)"m"$(CYAN)"i"$(BLUE)"n"$(MAGENTA)"i"$(RED)"s"$(YELLOW)"h"$(GREEN)"e"$(CYAN)"l"$(BLUE)"l"$(MAGENTA)"."$(RED)"."$(YELLOW)"." $(RESET)
	@rm -f $(OBJS)
	@make clean --no-print-directory -C $(LIB_DIR)
	@echo $(RED)"D"$(YELLOW)"o"$(GREEN)"n"$(CYAN)"e"$(BLUE)"!"$(MAGENTA)"!" $(RED)"🧹" $(RESET)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB_DIR)$(LIBFT)

re: fclean all

.PHONY: all clean fclean re