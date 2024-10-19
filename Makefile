# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 12:03:49 by mjameau           #+#    #+#              #
#    Updated: 2024/10/19 11:42:16 by mjameau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	main.c builtins/cd.c builtins/export.c builtins/echo.c builtins/pwd.c builtins/exit.c \
			builtins/unset.c exec/exec_utils.c exec/exec.c exec/more_exec.c exec/child_process.c builtins/ft_env.c \
			env.c error/free_exit.c tokens/create_token.c tokens/utils_token.c cmd.c path.c \
			signal/handle_signal.c parsing/syntax.c parsing/more_syntax.c parsing/even_more_syntax.c\

NAME	=	minishell

FLAGS	=	-Wall -Wextra -Werror -lreadline lib/libft.a -std=c99

RM		= rm -f

LIB_DIR	=	lib/
LIBFT 	=	libft.a

SRCS 	= $(addprefix ./srcs/, $(SRC))
OBJS	=	$(SRCS:.c=.o)

HEADER	=	minishell.h

all: $(LIB_DIR) $(LIBFT) $(NAME)

.c.o :
	@cc -g -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@echo "Compiling minishell..."
	@cc $(OBJS) $(FLAGS) -o $(NAME)
	@echo "Done!"

$(LIBFT):
	@echo "Making Libft"
	@make -C $(LIB_DIR)
	@echo "Done!"

clean:
	@echo "Cleaning..."
	@rm -f $(OBJS)
	@make clean -C $(LIB_DIR)
	@echo "Cleaning complete !"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB_DIR)$(LIBFT)

re: fclean all

.PHONY: all clean fclean re