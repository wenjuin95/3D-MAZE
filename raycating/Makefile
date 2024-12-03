NAME = raycasting
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OBJ = $(SRC:.c=.o)
SRC = main.c player.c

ifeq ($(shell uname), Linux)
	MINILIBX = ../minilibx-linux/
	MINILIBX_LIBRARY = -L$(MINILIBX) -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	MINILIBX = ../minilibx/
	MINILIBX_LIBRARY = -L$(MINILIBX) -lmlx -framework OpenGL -framework AppKit
endif

all : $(NAME)

$(NAME): $(OBJ)
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(SRC) $(MINILIBX_LIBRARY) -o $(NAME)

fclean:
	rm -f $(OBJ)
	rm -f $(NAME)
	@echo "${GREEN}-----FULLY REMOVE-----\n${RESET}"

re: fclean all
