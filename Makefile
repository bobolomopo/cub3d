# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jandre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 17:21:03 by jandre            #+#    #+#              #
#    Updated: 2020/11/25 21:18:08 by jandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIB = -I/usr/local/include -L/usr/local/lib -lmlx -L/usr/include -lm -lbsd -lX11 -lXext
SRC = test.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(SRC) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	sudo rm -rf *.o

fclean: clean
	sudo rm -rf Cub3D

re: fclean
	make all

.PHONY: all clean fclean re