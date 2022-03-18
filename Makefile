NAME = ray

SRC =	./Src/main.c ./Src/Draw/drawline.c ./Src/Draw/put_pixel.c ./Src/Draw/drawsquare.c ./Src/Draw/draw_map.c ./Src/Draw/draw_circle.c \
		./Src/Entity/Game/render.c ./Src/Entity/Game/update.c ./Src/Entity/Game/run.c \
		./Src/Entity/Player/render.c ./Src/Entity/Player/update.c ./Src/Ray/raycasting.c ./Src/Ray/get_rays.c \
		./Src/Ray/draw_rays.c \
		./Src/Util/reset_circle.c

OBJ = $(SRC:.c=.o)

CC = gcc

MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L./Src/Lib/Mlx/ -Imlx_linux -lXext -lX11 -lm -lz

VEC_LIB = ./Src/Lib/VecLib

CFLAGS= -g

INCLUDE = -I ./Include/ -I ./Src/Lib/VecLib/

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	make -C $(VEC_LIB)
	$(CC) $(CFLAGS)  $(INCLUDE) -o $(NAME) $(OBJ) $(MLX_FLAGS) -L$(VEC_LIB) -lvec -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	make re -C $(VEC_LIB)

.PHONY: re fclean clean
