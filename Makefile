# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 19:43:06 by dicisner          #+#    #+#              #
#    Updated: 2022/03/15 12:54:52 by jfrancis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g

SRC_DIR = src
PARSER_DIR = parser
BULTINS_DIR = builtins
EXECUTOR_DIR = executor

OBJ_DIR = build
LIBFT_DIR = libs/libft
INCLUDES_DIR = includes

LIBFT = $(LIBFT_DIR)/libft.a

BASE = main.c \
	test_fork.c \
	test_readline.c \

PARSE = parse.c \
	path_parser.c

BUILTINS = echo.c |
	cd.c

SRC = $(BASE) \
	$(PARSE) \
	$(BUILTINS)

SRC_FULL = $(addprefix $(SRC_DIR)/, $(BASE)) \
	$(addprefix $(SRC_DIR)/$(PARSER_DIR)/, $(PARSE)) \
	$(addprefix $(SRC_DIR)/$(BULTINS_DIR)/, $(BUILTINS))

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FULL))

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) -o $@ $^ -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(PARSER_DIR)
	mkdir -p $(OBJ_DIR)/$(BULTINS_DIR)
	mkdir -p $(OBJ_DIR)/$(EXECUTOR_DIR)
	$(CC) -I$(INCLUDES_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	echo cleaning!
	rm -rf $(NAME)
	echo done!

re: fclean all

install:
	sudo apt-get install libreadline-dev

.PHONY: all clean fclean re install
