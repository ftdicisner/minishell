# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dicisner <diegocl02@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 19:43:06 by dicisner          #+#    #+#              #
#    Updated: 2022/01/14 19:54:00 by dicisner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc

SRC_DIR = src

OBJ_DIR = build
INCLUDES_DIR = includes

FILES = main.c test.c
SRC = $(FILES)
SRC_ALL = $(addprefix $(SRC_DIR), $(FILES))
OBJECTS = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $@ $^ -lreadline 

%.o: $(SRC_DIR)/%.c
	$(CC) -I$(INCLUDES_DIR) -c $<

clean:
	$(RM) $(OBJECTS)

fclean:	clean
	echo cleaning!
	$(RM) $(NAME)
	echo done!

re: fclean all

install:
	sudo apt-get install libreadline-dev
	
.PHONY: all clean fclean re install
