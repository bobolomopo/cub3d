NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I
## Attention Flags MLX destiné au link Linux et pas MAC. ##
MLXFLAGS = -lmlx -lXext -lX11 -fPIC
LIB = minilibx.a

SRC := test.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[31m\033[1mcompiling...\033[0m"
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(LIB) $(SRC) -o $(NAME)
	@echo "Compiled!"

clean:
	@echo "\033[31m\033[1mcleaning...\033[0m"
	@rm -f $(OBJ)
	@echo "objects removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "cub3D removed!"

re: fclean
	@make



.PHONY: all clean fclean re cube3D
