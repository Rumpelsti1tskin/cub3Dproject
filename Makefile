CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx -I. #-fsanitize=address
MLXFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm
NAME = cub3D

INC = cub.h

SRC = cub.c \
		get_next_line.c \
		get_next_line_utils.c \
		add_funcs.c \
		add_funcs1.c \
		free_memory.c \
		free_memory1.c \
		free_memory2.c \
		init.c \
		init1.c \
		validate.c \
		validate1.c \
		validate2.c \
		validate3.c \
		validate4.c \
		validate5.c \
		raycasting_tex.c \
		raycasting1.c \
		raycasting2.c \
		raycasting3.c \
		raycasting4.c

OBJ = $(SRC:.c=.o)

.PHONY = NAME all clean fclean re

all: $(NAME)

$(NAME) : $(OBJ) Makefile cub.h minilibx-linux/libmlx.a
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

%.o : %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

minilibx-linux/libmlx.a:
	$(MAKE) -C minilibx-linux

clean :
		rm -f $(OBJ)

fclean : clean
		rm -f $(NAME)

re : fclean all