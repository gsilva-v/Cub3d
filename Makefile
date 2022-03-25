NAME = cub3D

CC = gcc
INCLUDE = -I ./include/
CFLAGS = -g  $(INCLUDE)
MLX_FLAGS = -lmlx_Linux -lXext -lX11

RM = rm -rf

PATH_SRCS = ./srcs/
PATH_CLOSE = $(PATH_SRCS)close/
PATH_DRAW = $(PATH_SRCS)draw/
PATH_INIT = $(PATH_SRCS)init/
PATH_MAIN = $(PATH_SRCS)main/
PATH_PARSE = $(PATH_SRCS)parse/
PATH_RAYS = $(PATH_SRCS)rays/
PATH_UTILS = $(PATH_SRCS)utils/

PATH_ENTITY = $(PATH_SRCS)entity/
PATH_GAME = $(PATH_ENTITY)game/
PATH_PLAYER = $(PATH_ENTITY)player/

PATH_LIBS = $(PATH_SRCS)lib/
PATH_VEC = $(PATH_LIBS)vec_lib/
PATH_LIBFT = $(PATH_LIBS)libft/

PATH_OBJS = ./objs/
OBJ_PATH = ./objs/

SRCS += $(addprefix $(PATH_CLOSE), kill_window finish_him)
SRCS += $(addprefix $(PATH_DRAW), draw_pixel)
SRCS += $(addprefix $(PATH_GAME), update render run)
SRCS += $(addprefix $(PATH_PLAYER), update render watch watch_utils)
SRCS += $(addprefix $(PATH_INIT), init_game load_imgs start_orientation)
SRCS += $(addprefix $(PATH_MAIN), main)
SRCS += $(addprefix $(PATH_PARSE), parse_map parse_map_utils parse_resources parse_resources_utils  parse_resources_utils2)
SRCS += $(addprefix $(PATH_RAYS), rays rays_render_engine rays_render_utils color)
SRCS += $(addprefix $(PATH_UTILS), gnl matrix_len free_matrix distance check_ext)
  
SRC = $(addsuffix .c, $(SRCS))

OBJS = $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRC))


all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
	@echo " 100% complete"
	@echo -n "libft     : "
	@make --no-print-directory -C $(PATH_LIBFT)
	@echo " 100% complete"
	@echo -n "vector lib     : "
	@make --no-print-directory -C $(PATH_VEC)
	@echo " 100% complete"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) -lm -L$(PATH_VEC) -lvec -L$(PATH_LIBFT) -lft

$(OBJ_PATH):
	@echo -n "Cub3D : "
	@mkdir -p  $(PATH_OBJS)
	@mkdir -p  $(PATH_OBJS)close/
	@mkdir -p  $(PATH_OBJS)draw/
	@mkdir -p  $(PATH_OBJS)entity/
	@mkdir -p  $(PATH_OBJS)entity/game
	@mkdir -p  $(PATH_OBJS)entity/player
	@mkdir -p  $(PATH_OBJS)init/
	@mkdir -p  $(PATH_OBJS)main/
	@mkdir -p  $(PATH_OBJS)parse/
	@mkdir -p  $(PATH_OBJS)rays/
	@mkdir -p  $(PATH_OBJS)utils/
	@echo -n "\033[1;32m█\033[0m"

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(MLX_FLAGS) -lm
	@echo -n "\033[1;32m█\033[0m"

clean:	
	@echo "Deleted data!"
	@$(RM) ./objs

fclean: clean
	@make --no-print-directory fclean -C $(PATH_LIBFT)
	@make --no-print-directory fclean -C $(PATH_VEC)
	@$(RM) $(NAME)

re: fclean all

run: re
	./cub3D ./maps/simple_map.cub 

runv: re
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./maps/simple_map.cub 

.PHONY: all clean fclean re