NAME = cub3d

CC = gcc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE)
MLX_FLAGS = -lmlx_Linux -lXext -lX11

RM = rm -rf

PATH_SRCS = ./srcs/
PATH_MAIN = $(PATH_SRCS)main/
PATH_CLOSE = $(PATH_SRCS)close_game/
PATH_DRAW = $(PATH_SRCS)draw/
PATH_INIT = $(PATH_SRCS)init/
PATH_RENDMAP = $(PATH_SRCS)render_map/
PATH_RAYS = $(PATH_SRCS)rays/
PATH_UTILS = $(PATH_SRCS)utils/
PATH_PARSE = $(PATH_SRCS)parse/
PATH_ENTITY = $(PATH_SRCS)entity/
PATH_GAME = $(PATH_ENTITY)game/
PATH_PLAYER = $(PATH_ENTITY)player/

PATH_LIBS = $(PATH_SRCS)lib/
PATH_VEC = $(PATH_LIBS)vec_lib/
PATH_LIBFT = $(PATH_LIBS)libft/

PATH_OBJS = ./objs/

SRCS += $(addprefix $(PATH_MAIN), main)
SRCS += $(addprefix $(PATH_CLOSE), kill_window)
SRCS += $(addprefix $(PATH_DRAW), draw_pixel draw_map)
SRCS += $(addprefix $(PATH_GAME), update render run)
SRCS += $(addprefix $(PATH_PLAYER), update render watch watch_utils)
SRCS += $(addprefix $(PATH_INIT), init_game load_imgs)
SRCS += $(addprefix $(PATH_PARSE), parse_map parse_resources)
SRCS += $(addprefix $(PATH_RAYS), rays rays_render_engine rays_render_utils color)
SRCS += $(addprefix $(PATH_UTILS), gnl matrix_len)
  
SRC = $(addsuffix .c, $(SRCS))

OBJS = $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PATH_LIBFT)
	make -C $(PATH_VEC)
	$(CC) $(CFLAGS) ./objs/*/*.o ./objs/*/*/*.o -o $(NAME) $(MLX_FLAGS) -lm -L$(PATH_VEC) -lvec -L$(PATH_LIBFT) -lft

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c
		@mkdir -p  $(PATH_OBJS)
		@mkdir -p  $(PATH_OBJS)close_game/
		@mkdir -p  $(PATH_OBJS)main/
		@mkdir -p  $(PATH_OBJS)init/
		@mkdir -p  $(PATH_OBJS)draw/
		@mkdir -p  $(PATH_OBJS)entity/
		@mkdir -p  $(PATH_OBJS)entity/game
		@mkdir -p  $(PATH_OBJS)entity/player
		@mkdir -p  $(PATH_OBJS)parse/
		@mkdir -p  $(PATH_OBJS)rays/
		@mkdir -p  $(PATH_OBJS)utils/
		$(CC) $(CFLAGS) -c $< -o $@ $(MLX_FLAGS) -lm

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./cub3d ./maps/simple_map.cub 
runv: re
	valgrind ./cub3d ./maps/simple_map.cub 
.PHONY: all clean fclean re