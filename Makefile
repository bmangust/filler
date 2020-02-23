# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akraig <akraig@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 12:00:21 by akraig            #+#    #+#              #
#    Updated: 2020/02/23 12:46:12 by akraig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = akraig.filler

PLAYERDIR = ./resources/players

SRC_DIR = ./src

OBJ_DIR = ./obj

INC_DIR = ./inc

LIB_DIR = ./printf

LIB_INC_DIR = $(LIB_DIR)/inc

LIBRARIES = -L$(LIB_DIR) -lftprintf

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I$(INC_DIR) -I$(LIB_INC_DIR)

SRC =	array_list.c \
		dots.c \
		error.c \
		main.c \
		map.c \
		moves.c \
		piece.c \

OBJ = $(SRC:.c=.o)

OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

NAMEDIR = @(addprefix @(PLAYERDIR)/, $(NAME))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(NAMEDIR)
	@echo "Compiling libft. Please wait..."
	@make -C printf/
	@echo "libft done"
	@echo "compiling filler"
	@gcc -o $(PLAYERDIR)/$(NAME) $(OBJS) $(INCLUDES) $(LIBRARIES)
	@echo "We're ready to work"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NAMEDIR):
	mkdir -p $(PLAYERDIR)

clean:
	@echo "cleaninig"
	@make -C $(LIB_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "objects removed"

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)
	@echo "Cleaning is done. Directory is ready"

re: fclean all

game:
	resources/filler_vm -f resources/maps/map00 -p1 resources/players/$(p1).filler -p2 resources/players/$(p2).filler

champ:
	resources/filler_vm -t 1 -f resources/maps/map02 -p1 resources/players/$(p1).filler -p2 resources/players/$(p2).filler

