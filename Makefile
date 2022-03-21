NAME = cub3d

CC = gcc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE)
MLX_FLAGS = -lmlx_Linux -L/usr/lib/X11/ -lXext -lX11

RM = rm -rf

PATH_SRCS = ./srcs/
PATH_MAIN = $(PATH_SRCS)main/
PATH_LIBS = $(PATH_SRCS)libs/
PATH_CLOSE = $(PATH_SRCS)close_game/
PATH_DRAW = $(PATH_SRCS)draw/
PATH_INIT = $(PATH_SRCS)init/
PATH_MOVE = $(PATH_SRCS)moves/
PATH_MAP = $(PATH_SRCS)map/
PATH_RENDMAP = $(PATH_SRCS)render_map/
PATH_RAYS = $(PATH_SRCS)rays/
PATH_UTILS = $(PATH_SRCS)utils/

PATH_VEC = $(PATH_LIBS)vec_lib/

PATH_OBJS = ./objs/

SRCS =   $(PATH_MAIN)main.c\
		$(PATH_CLOSE)kill_window.c\
		$(PATH_DRAW)draw_line.c $(PATH_DRAW)draw_pixel.c $(PATH_DRAW)draw_square.c\
		$(PATH_DRAW)draw_map.c\
		$(PATH_INIT)init_game.c $(PATH_INIT)load_imgs.c\
		$(PATH_MAP)render3d.c\
		$(PATH_MOVE)handle_move.c\
		$(PATH_RENDMAP)render_map.c\
		$(PATH_RAYS)rays.c $(PATH_RAYS)rays_set_values.c $(PATH_RAYS)rays_utils.c\
		$(PATH_UTILS)ft_calloc.c

OBJS = $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PATH_VEC)
	$(CC) $(CFLAGS) ./objs/*/*.o -o $(NAME) $(MLX_FLAGS) -lm -L$(PATH_VEC) -lvec

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c
		@mkdir -p $(PATH_OBJS)
		@mkdir -p $(PATH_OBJS)close_game/
		@mkdir -p $(PATH_OBJS)main/
		@mkdir -p $(PATH_OBJS)map/
		@mkdir -p $(PATH_OBJS)init/
		@mkdir -p $(PATH_OBJS)render_map/
		@mkdir -p $(PATH_OBJS)draw/
		@mkdir -p $(PATH_OBJS)moves/
		@mkdir -p $(PATH_OBJS)rays/
		@mkdir -p $(PATH_OBJS)utils/
		$(CC) $(CFLAGS) -c $< -o $@ $(MLX_FLAGS) -lm

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re