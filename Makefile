# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/21 11:32:21 by jebrocho          #+#    #+#              #
#    Updated: 2019/04/09 18:01:43 by jebrocho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/ft_split.c src/ft_split_whitespace.c src/error.c \
	  	src/env.c src/builtin.c src/tools.c src/split_env.c src/cd.c src/echo.c \
			src/tools_builtin.c src/setenv.c

OBJ = $(SRC: .c=.o)

LIB = libft/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	@echo "Compilation..."
	@$(CC) $(FLAGS) $(LIB) -I./libft $(OBJ) -I./includes -o $(NAME)
	@echo "OK."

$(LIB):
	@make -C libft/ fclean
	@make -C libft/

%.o: %.c
	$(CC) -o $@ -c $< -I./includes

clean:
	@echo "Deleting all object file ..."
	@make -C libft/ clean
	@echo "OK."

fclean:
	@echo "Deleting ./ft_ls"
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo "OK."

re: fclean all

.PHONY: clean fclean re all
