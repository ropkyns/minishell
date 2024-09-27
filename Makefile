# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 12:03:49 by mjameau           #+#    #+#              #
#    Updated: 2024/09/27 10:19:59 by mjameau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	main.c builtins/cd.c builtins/export.c builtins/echo.c builtins/pwd.c env.c error.c tokens/create_token.c \
			tokens/utils_token.c cmd.c path.c signal/handle_signal.c

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
	@cc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

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