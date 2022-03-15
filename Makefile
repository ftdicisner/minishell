# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 13:10:18 by jfrancis          #+#    #+#              #
#    Updated: 2022/03/15 13:12:29 by jfrancis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g

SRC_DIR = src
PARSER_DIR = parser
BULTINS_DIR = builtins
EXECUTOR_DIR = executor
ENV_DIR = env

OBJ_DIR = build
LIBFT_DIR = libs/libft
INCLUDES_DIR = includes

LIBFT = $(LIBFT_DIR)/libft.a

BASE = main.c \
	test_fork.c \
	test_readline.c \
	utils.c

PARSE = parse.c \
	path_parser.c

BUILTINS = echo.c \
	cd.c

ENV = env.c \
	export.c \
	unset.c

SRC = $(BASE) \
	$(PARSE) \
	$(BUILTINS) \
	$(ENV)

SRC_FULL = $(addprefix $(SRC_DIR)/, $(BASE)) \
	$(addprefix $(SRC_DIR)/$(PARSER_DIR)/, $(PARSE)) \
	$(addprefix $(SRC_DIR)/$(BULTINS_DIR)/, $(BUILTINS)) \
	$(addprefix $(SRC_DIR)/$(ENV_DIR)/, $(ENV)) \

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
	mkdir -p $(OBJ_DIR)/$(ENV_DIR)
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
