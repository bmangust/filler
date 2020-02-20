# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akraig <akraig@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 12:00:21 by akraig            #+#    #+#              #
#    Updated: 2020/01/23 12:27:16 by akraig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = akraig.filler

SRC_DIR = ./src

OBJ_DIR = ./obj

INC_DIR = ./inc

LIB = -L. -lftprintf

FLAGS = -Wall -Werror -Wextra

MAKELIB = printf/Makefile

SRC =	array_list.c \
		dots.c \
		error.c \
		main.c \
		map.c \
		moves.c \
		piece.c \

OBJ = $(SRC:.c=.o)

OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

all: $(OBJ_DIR) $(NAME)

$(NAME): lib $(OBJS)
	@gcc -o $(NAME) $(OBJS) -I $(INC_DIR) $(LIB)

lib:
	make -f $(MAKELIB)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc $(FLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR) 

fclean: clean
	rm -f $(NAME)

re: fclean all
