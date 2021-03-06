/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:29:29 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/04 09:11:50 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/X.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <get_next_line.h>
# include "../libs/vec_lib/vec.h"
# include "../libs/libft/libft.h"

# define BLOCK_SIZE 64
# define ESC 0xff1b
# define PI 3.141592653589f
# define SCREENHEIGHT 430
# define SCREENWIDTH 700
# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define VALID_BLOCK "01 \nWENS"
# define HAS_INSIDE "ESWN02"
# define WRONG_ARG  "Invalid arguments, try ./cub3d ./maps/simple_map.cub"
# define INV_CFG "This map have any misconfiguration, see ./maps/example.cub"
# define WTOUT_PLYR "this map dont have a initial point for player"
# define DBLE_PLYR "This map have 2 or more initial points to player"
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define SHIFT 65505

typedef struct s_buttons
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	exit;
	int	rotate_right;
	int	rotate_left;
	int	function;
	int	acelerate;
	int	light;
}	t_buttons;

typedef struct s_data{
	char	*name;
	char	*addr;
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_texture{
	int		line_height;
	int		start_line;
	int		end_line;
	int		texture_x;
	int		texture_y;
	double	texture_pos;
	double	step;
	t_data	*data;
}	t_texture;

typedef struct s_rays{
	t_int_vec	map_pos;
	t_vec		ray_dir;
	double		dlt_x;
	double		dlt_y;
	double		dst_x;
	double		dst_y;
	double		perp_wall;
	int			rays;
	int			hit_side;
	int			step_x;
	int			step_y;
}	t_rays;

typedef struct s_player{
	t_vec	pos;
	t_vec	plane;
	t_vec	direction;
	float	movespeed;
}	t_player;

typedef struct s_block{
	t_data	no;
	t_data	so;
	t_data	we;
	t_data	ea;
}	t_block;

typedef struct s_resource {
	t_data	canvas;
	t_block	wall;
	int		ceil_color;
	int		floor_color;
}	t_resource;

typedef struct s_game{
	t_player	player;
	t_buttons	buttons;
	char		*buffer;
	t_resource	resources;
	void		*mlx;
	void		*win;
	char		**map;
}	t_game;

// INIT
void	init_game(t_game *game);
void	load_imgs(t_game *game);

// START ORIENTATION
void	player_north(t_game *game, int x, int y);
void	player_south(t_game *game, int x, int y);
void	player_west(t_game *game, int x, int y);
void	player_east(t_game *game, int x, int y);

// PARSE
int		parse_map(t_game *game, char *file);
int		parse_resources(t_game *game, char *file);

// PARSE MAP UTILS
int		check_horizontal_wall(char **map, int x, int y);
int		check_vertical_wall(char **map, int x, int y);
int		check_diagonalup_wall(char **map, int x, int y);
int		check_diagonaldown_wall(char **map, int x, int y);

// PARSE RESOURCE UTILS
int		valid_conf(char **config);
int		set_config(t_game *game, char **config);
int		set_color_background(t_game *game, char **config);

// COLOR
int		create_rgb(int r, int g, int b);
int		get_pixel(t_data *data, t_vec point);
int		lamp(int x, int y, t_game *game, int color);
int		reshade(int main_color, int have_reshade);

// DRAW
void	draw_pixel(t_data *data, t_vec vec, int color);

// GAME ENTITY
int		game_render(t_game *game);
void	game_run(t_game *game);
void	game_update(t_game *game);

// PLAYER ENTITY
void	player_render(t_game *game);
void	player_update(t_game *game);

// WATCH MOVES
void	watch_walk(t_game *game);
void	watch_rotate(t_game *game);
void	watch_strafe(t_game *game);
void	watch_functions(t_game *game);

// WATCH UTILS
void	change_plane(t_game *game, float rot_speed);
void	change_direction(t_game *game, float rot_speed);

// MAP
int		update_map(int key_code, t_game *game);

// RAYS
void	raycasting(t_game *game);
void	dda(t_rays *values, t_game *game);

// RENDER ENGINE
void	render_engine(t_rays *values, t_game *game);

// RENDER ENGINE UTILS
t_data	*get_texture(t_game *game, t_rays *values);
void	set_perp_wall(t_rays *values, t_game *game);
void	check_transparence(t_game *game, t_rays *values);

// CLOSE
void	finish_him(t_game *game, int exit_code);
void	kill_window(t_game *game);
void	show_error(t_game *game, int exit_code, char *s);
int		red_cross(t_game *game);

// UTILS
int		matrix_len(char **matrix);
void	free_matrix(char **matrix);
int		distance(t_vec a, t_vec b);
int		check_ext(char *file, char *ext);

#endif
