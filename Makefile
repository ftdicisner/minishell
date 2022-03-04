# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 19:43:06 by dicisner          #+#    #+#              #
#    Updated: 2022/03/04 08:48:47 by dicisner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g

SRC_DIR = src
PARSER_DIR = parser
EXECUTOR_DIR = executor

OBJ_DIR = build
LIBFT_DIR = libs/libft
INCLUDES_DIR = includes

LIBFT = $(LIBFT_DIR)/libft.a

BASE = main.c \
	test_fork.c \
	test_readline.c \

PARSE = parse.c
	
SRC = $(BASE) \
	$(PARSE)

SRC_FULL = $(addprefix $(SRC_DIR)/, $(BASE)) \
	$(addprefix $(SRC_DIR)/$(PARSER_DIR)/, $(PARSE))

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FULL))

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) -o $@ $^ -lreadline 

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(PARSER_DIR)
	mkdir -p $(OBJ_DIR)/$(EXECUTOR_DIR)
	$(CC) -I$(INCLUDES_DIR) -c $< -o $@

# 

# build/parse/parse.o: src/parse/parse.c
#	gcc -o src/parse/parse.c build/parse/parse.o

# build/main.o: src/main.c
#	gcc -o src/main.c build/main.o

# ...

clean:
	$(RM) $(OBJ_DIR)

fclean:	clean
	echo cleaning!
	$(RM) $(NAME)
	echo done!

re: fclean all

install:
	sudo apt-get install libreadline-dev
	
.PHONY: all clean fclean re install
