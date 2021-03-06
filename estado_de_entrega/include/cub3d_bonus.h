/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:29:27 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/04 09:17:32 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <mlx.h>
# include <X11/X.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include <time.h>
# include <get_next_line.h>
# include "../libs/vec_lib/vec.h"
# include "../libs/libft/libft.h"

# define BLOCK_SIZE 64
# define MBS 10
# define MAP_WIDTH 100
# define MAP_HEIGHT 100
# define ESC 0xff1b
# define PI 3.141592653589f
# define SCREENHEIGHT 430
# define SCREENWIDTH 700
# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define OPEN_DOOR '3'
# define VALID_BLOCK "0123FG \nWENS"
# define HAS_INSIDE "ESWN023FG"
# define WRONG_ARG  "Invalid arguments, try ./cub3d ./maps/simple_map.cub"
# define INV_CFG "This map have any misconfiguration, see ./maps/example.cub"
# define WTOUT_PLYR "this map dont have a initial point for player"
# define DBLE_PLYR "This map have 2 or more initial points to player"
# define WIN " You win, congrats! "
# define LOSE " You lose, try again! "
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define SHIFT 65505
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0

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
	int		bpp;
	int		width;
	int		height;
	int		line_len;
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

typedef struct s_animation
{
	t_data	*sprites;
	int		index;
	int		n_sprites;
	float	seconds;
}	t_animation;

typedef struct s_entity
{
	t_data			sprite;
	t_animation		animation;
	t_vec			pos;
	int				is_on_view;
	int				found_player;
}	t_entity;

typedef struct s_player{
	t_vec	pos;
	t_vec	plane;
	t_vec	direction;
	float	rotate_cam;
	float	movespeed;
}	t_player;

typedef struct s_block{
	t_data	no;
	t_data	so;
	t_data	we;
	t_data	ea;
}	t_block;

typedef struct s_resource {
	t_data		g_sprite;
	t_animation	g_animation;
	t_data		enemy;
	t_data		canvas;
	t_data		map;
	t_data		floor;
	t_block		wall;
	t_block		door;
	t_block		open_door;
	int			ceil_color;
	int			floor_color;
}	t_resource;

typedef struct s_sprite{
	t_vec		pos;
	double		inv_delta;
	t_vec		trans;
	int			sprite_screen;
	int			v_move_screen;
	int			sprite_h;
	int			sprite_w;
	t_int_vec	draw_start;
	t_int_vec	draw_end;
	int			stripe;
	t_int_vec	text;
}	t_sprite;

typedef struct s_floor{
	t_vec		raydir0;
	t_vec		raydir1;
	t_vec		step;
	t_vec		pos;
	t_int_vec	text;
	float		row_dist;
}	t_floor;

typedef struct s_game{
	t_player	player;
	t_buttons	buttons;
	char		*buffer;
	float		*z_buffer;
	int			is_on_focus;
	t_resource	resources;
	t_entity	*ghost;
	t_entity	final;
	t_vec		map_offset;
	int			enemy_on_view;
	void		*mlx;
	void		*win;
	char		**map;
	int			is_open_door;
	double		last_time;
	double		elapsed_time;
	int			n_ghost;
	int			lose;
}	t_game;

// TIME
double	passed_time(long time_started);
long	current_time(void);

// MINIMAP
void	minimap(t_game *game);
int		get_higher_len(char **matrix);
void	clean_minimap(t_game *game);
void	draw_map(t_game *game);
void	get_and_draw(t_game *game, t_vec canv_pos, t_vec t_pos, t_data *text);

// SPRITE
void	draw_sprite(t_game *game, t_vec pos, t_data *text);
int		sprite_render(t_game *game);
int		sprite_update(t_game *game);
void	ghost_on_view(t_game *game, t_vec ray_dir);
void	reset_ghost_view(t_game *game);
void	is_on_view(t_game *game, t_entity *entity, t_vec ray_dir);

//  MOUSE
int		enter_window(t_game *game);
int		leave_window(t_game *game);
int		rotate(int x, int y, t_game *game);

// INIT
void	init_game(t_game *game);
void	load_imgs(t_game *game);

// INIT UTILS
int		get_number_ghost(t_game *game);
int		player_on_view(char **map, int x, int y);
void	move_minimap_cam(t_game *game);

// LOAD IMGS
int		open_xpm_file(t_data *d, t_game *game);
void	init_animation(t_game *game, t_animation *anim, char *name, int n_spr);

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
void	normalize_map(t_game *game);
int		check_diagonalup_wall(char **map, int x, int y);

// PARSE RESOURCE UTILS
int		valid_conf(char **config);
int		set_config(t_game *game, char **config);
int		set_color_background(t_game *game, char **config);

// COLOR
int		create_rgb(int r, int g, int b);
int		get_pixel(t_data *data, t_vec point);
int		lamp(t_vec pos, t_game *game, int color, float dist);
int		reshade(int main_color);
int		get_color_shade(int color, double qnt_shade);

// DRAW
void	draw_pixel(t_data *data, t_vec vec, int color);
void	draw_circle(t_vec position, int radius, t_data *data, int color);
void	draw_line(t_vec vec1, t_vec vec2, int color, t_game *game);

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
void	handle_cam_x(t_game *game, t_vec map_pos);
void	change_plane(t_game *game, float rot_speed);
void	change_direction(t_game *game, float rot_speed);
void	move_cam_x(t_game *game, t_vec velocity);
void	move_cam_y(t_game *game, t_vec velocity);

// MAP
int		update_map(int key_code, t_game *game);

// FLOOR
void	floor_casting(t_game *game);

// RAYS
void	raycasting(t_game *game);
void	dda(t_rays *values, t_game *game);
void	check_open_wall(t_game *game, t_rays *values);

// RENDER ENGINE
void	render_engine(t_rays *values, t_game *game);

// RENDER ENGINE UTILS
t_data	*get_texture(t_game *game, t_rays *values);
void	set_perp_wall(t_rays *values, t_game *game);
void	check_transparence(t_game *game, t_rays *values);
int		set_color(t_game *game, int color, t_rays *values, int index);

// CLOSE
void	finish_him(t_game *game, int exit_code);
void	kill_window(t_game *game);
void	show_error(t_game *game, int exit_code, char *s);
int		red_cross(t_game *game);

// FREE
void	free_data(t_game *game, t_data *data);
void	free_block(t_block *block, t_game *game);
void	free_animation(t_animation *animation, t_game *game);
void	free_sprite(t_entity *who, t_game *game);

// UTILS
int		matrix_len(char **matrix);
void	free_matrix(char **matrix);
int		distance(t_vec a, t_vec b);
int		check_ext(char *file, char *ext);

#endif
