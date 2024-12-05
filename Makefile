NAME = cub3d

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g3

# directory that contains source files
FILE_DIR = src src/parse

# specify the directory where make should look for files
vpath %.c $(FILE_DIR)

# list all ".c" in the specified directories
SRC = $(foreach dir, $(FILE_DIR), $(wildcard $(dir)/*.c))

INC = -I include

OBJ_FOLDER = object_files

OBJ_SRC = $(addprefix $(OBJ_FOLDER)/, $(notdir $(SRC:.c=.o)))

LIBFT_DIR = libft/libft.a

# color
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

# check for OS
ifeq ($(shell uname), Linux)
	MINILIBX = minilibx-linux/
	MINILIBX_LIBRARY = -L$(MINILIBX) -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	MINILIBX = minilibx/
	MINILIBX_LIBRARY = -L$(MINILIBX) -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME) : $(OBJ_SRC)
	make -C $(MINILIBX)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ_SRC) $(INC) $(LIBFT_DIR) $(MINILIBX_LIBRARY) -o $(NAME)
	@echo "${GREEN}-----COMPILED DONE-----\n${RESET}"

$(OBJ_FOLDER)/%.o : %.c
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_FOLDER)
	make fclean -C libft
	make clean -C $(MINILIBX)
	rm -f libft.a

fclean : clean
	rm -f $(NAME)
	@echo "${GREEN}-----FULLY REMOVE-----\n${RESET}"

re : fclean all

norm:
	@echo "${BLUE}\n-----CHECK SRC-----${RESET}"
	@norminette src/*.c
	@echo "${BLUE}\n-----CHECK INCLUDE-----${RESET}"
	@norminette include/*.h
	@echo "${BLUE}\n-----CHECK LIBFT-----${RESET}"
	@norminette libft/*.c libft/*.h

.PHONY : all clean fclean re bonus