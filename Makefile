# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 12:03:49 by mjameau           #+#    #+#              #
#    Updated: 2024/09/13 16:30:12 by paulmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	main.c

NAME	=	minishell

FLAGS	=	-Wall -Wextra -Werror -lreadline

RM		= rm -f

LIB_DIR	=	lib/
LIBFT 	=	libft.a

SRCS 	= $(addprefix ./srcs/, $(SRC))
OBJS	=	$(SRCS:.c=.o)

HEADER	=	minishell.h

all: $(NAME) $(LIB_DIR) $(LIBFT)

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