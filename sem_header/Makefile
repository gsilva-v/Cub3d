NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = gcc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE)
MLX_FLAGS = -lmlx -lXext -lX11

RM = rm -rf
PATH_LIBS = ./libs/
PATH_VEC = $(PATH_LIBS)vec_lib/
PATH_LIBFT = $(PATH_LIBS)libft/

# MANDATORY MACROS
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

# BONUS MACROS 
PATH_SRCS_B = ./srcs_bonus/
PATH_CLOSE_B = $(PATH_SRCS_B)close_bonus/
PATH_DRAW_B = $(PATH_SRCS_B)draw_bonus/
PATH_INIT_B = $(PATH_SRCS_B)init_bonus/
PATH_MAIN_B = $(PATH_SRCS_B)main_bonus/
PATH_PARSE_B = $(PATH_SRCS_B)parse_bonus/
PATH_RAYS_B = $(PATH_SRCS_B)rays_bonus/
PATH_UTILS_B = $(PATH_SRCS_B)utils_bonus/

PATH_ENTITY_B = $(PATH_SRCS_B)entity_bonus/
PATH_GAME_B = $(PATH_ENTITY_B)game_bonus/
PATH_PLAYER_B = $(PATH_ENTITY_B)player_bonus/
PATH_SPRITE_B = $(PATH_ENTITY_B)sprite_bonus/

PATH_OBJS_B = ./objs_bonus/
OBJ_PATH_B = ./objs_bonus/

SRCS_B += $(addprefix $(PATH_CLOSE_B), free_zone_bonus kill_window_bonus finish_him_bonus)
SRCS_B += $(addprefix $(PATH_DRAW_B), draw_pixel_bonus minimap_bonus draw_sprite_bonus draw_circle_bonus draw_line_bonus)
SRCS_B += $(addprefix $(PATH_GAME_B), mouse_handle_bonus update_bonus render_bonus run_bonus)
SRCS_B += $(addprefix $(PATH_PLAYER_B), update_bonus render_bonus watch_bonus watch_utils_bonus)
SRCS_B += $(addprefix $(PATH_SPRITE_B), update_bonus render_bonus)
SRCS_B += $(addprefix $(PATH_INIT_B), init_utils_bonus init_game_bonus load_imgs_bonus load_utils_bonus start_orientation_bonus)
SRCS_B += $(addprefix $(PATH_MAIN_B), main_bonus)
SRCS_B += $(addprefix $(PATH_PARSE_B), parse_map_bonus parse_map_utils_bonus parse_resources_bonus parse_resources_utils_bonus parse_resources_utils2_bonus)
SRCS_B += $(addprefix $(PATH_RAYS_B), floor_bonus rays_bonus rays_render_engine_bonus rays_render_utils_bonus color_bonus transparence_bonus)
SRCS_B += $(addprefix $(PATH_UTILS_B), gnl_bonus time_bonus matrix_len_bonus free_matrix_bonus distance_bonus check_ext_bonus)
  
SRC_B = $(addsuffix .c, $(SRCS_B))

OBJS_BONUS = $(patsubst $(PATH_SRCS_B)%.c, $(PATH_OBJS_B)%.o, $(SRC_B))

# MANDATORY COMPILATION
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

# BONUS COMPILATION
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_PATH_B) $(OBJS_BONUS)
	@echo " 100% complete"
	@echo -n "libft     : "
	@make --no-print-directory -C $(PATH_LIBFT)
	@echo " 100% complete"
	@echo -n "vector lib     : "
	@make --no-print-directory -C $(PATH_VEC)
	@echo " 100% complete"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS) $(MLX_FLAGS) -lm -L$(PATH_VEC) -lvec -L$(PATH_LIBFT) -lft

$(OBJ_PATH_B):
	@echo -n "Cub3D : "
	@mkdir -p  $(PATH_OBJS_B)
	@mkdir -p  $(PATH_OBJS_B)close_bonus/
	@mkdir -p  $(PATH_OBJS_B)draw_bonus/
	@mkdir -p  $(PATH_OBJS_B)entity_bonus/
	@mkdir -p  $(PATH_OBJS_B)entity_bonus/game_bonus
	@mkdir -p  $(PATH_OBJS_B)entity_bonus/player_bonus
	@mkdir -p  $(PATH_OBJS_B)entity_bonus/sprite_bonus
	@mkdir -p  $(PATH_OBJS_B)init_bonus/
	@mkdir -p  $(PATH_OBJS_B)main_bonus/
	@mkdir -p  $(PATH_OBJS_B)parse_bonus/
	@mkdir -p  $(PATH_OBJS_B)rays_bonus/
	@mkdir -p  $(PATH_OBJS_B)utils_bonus/
	@echo -n "\033[1;32m█\033[0m"

$(PATH_OBJS_B)%.o: $(PATH_SRCS_B)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(MLX_FLAGS) -lm
	@echo -n "\033[1;32m█\033[0m"

clean:	
	@echo "Deleted data!"
	@$(RM) ./objs
	@$(RM) ./objs_bonus

fclean: clean
	@make --no-print-directory fclean -C $(PATH_LIBFT)
	@make --no-print-directory fclean -C $(PATH_VEC)
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

run: re
	./cub3D ./maps/simple_map.cub 

runv: re
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./maps/simple_map.cub 

.PHONY: all clean fclean re