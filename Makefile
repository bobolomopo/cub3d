# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jandre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 17:21:03 by jandre            #+#    #+#              #
#    Updated: 2020/12/03 16:10:53 by jandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIB_LIN = -I/usr/local/include -L/usr/local/lib -lmlx -L/usr/include -lm -lbsd -lX11 -lXext
LIB_MAC = -lmlx -lmlx -framework Appkit
SRC = game.c parsing/*.c gnl/*.c utils/*.c raycasting/*.c
INC = /include
PARSING = parsing/*.c gnl/*.c utils/*.c main.c raycasting/*.c 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(SRC) -g -fsanitize=address -lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

parsing:
	$(CC) -Wall -Wextra -Werror $(PARSING) -I $(INC)

clean:
	rm -rf *.o

fclean: clean
	rm -rf Cub3D

re: fclean
	make all

.PHONY: all clean fclean re
