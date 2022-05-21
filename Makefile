# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 13:10:18 by jfrancis          #+#    #+#              #
#    Updated: 2022/05/21 18:04:18 by dicisner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g

SRC_DIR = src
PARSER_DIR = parser
BULTINS_DIR = builtins
EXECUTOR_DIR = executor
ENV_DIR = env
UTILS_DIR = utils

OBJ_DIR = build
LIBFT_DIR = libs/libft
INCLUDES_DIR = includes

LIBFT = $(LIBFT_DIR)/libft.a

BASE = main.c \
	test_fork.c \
	test_readline.c

PARSE = parser.c \
	path_parser.c \
	env_parser.c \
	redir_parser.c \
	cmd_parser.c

EXECUTOR = executor.c \
	executables.c \
	pipes.c \
	pipes_out.c \
	signals.c \
	pipes_in.c

BUILTINS = echo.c \
	cd.c \
	pwd.c \
	env.c \
	exit.c \
	export.c \
	unset.c

UTILS = error.c \
		utils.c \
		utils2.c

SRC = $(BASE) \
	$(PARSE) \
	$(BUILTINS) \
	$(ENV) \
	$(UTILS)

SRC_FULL = $(addprefix $(SRC_DIR)/, $(BASE)) \
	$(addprefix $(SRC_DIR)/$(PARSER_DIR)/, $(PARSE)) \
	$(addprefix $(SRC_DIR)/$(BULTINS_DIR)/, $(BUILTINS)) \
	$(addprefix $(SRC_DIR)/$(ENV_DIR)/, $(ENV)) \
	$(addprefix $(SRC_DIR)/$(EXECUTOR_DIR)/, $(EXECUTOR)) \
	$(addprefix $(SRC_DIR)/$(UTILS_DIR)/, $(UTILS))

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
	mkdir -p $(OBJ_DIR)/$(UTILS_DIR)
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

valgrindtest:
	valgrind --suppressions=readline.supp --track-fds=yes ./minishell

.PHONY: all clean fclean re install
