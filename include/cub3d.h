#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <get_next_line.h>
# include "../srcs/lib/vec_lib/vec.h"
# include "../srcs/lib/libft/libft.h"

# define BLOCK_SIZE 64
# define ESC 0xff1b
# define PI 3.141592653589f
# define screenHeight 700
# define screenWidth 1200
# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define VALID_BLOCK "012 \nWENS"

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
}	t_buttons;

typedef struct	s_data {
	char	*name;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_texture{
	int	line_height;
	int start_line;
	int end_line;
	int texture_x;
	int texture_y;
	double texture_pos;
	double step;
	t_data *data;

} t_texture;

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


typedef struct	s_player {
	t_vec		pos;
	t_vec		plane;
	t_vec		direction;
} t_player;

typedef struct s_block{
	t_data	no;//norte cima
	t_data	so;//sul baixo
	t_data	we;//oeste <- esquerda
	t_data	ea;//leste -> direita
}	t_block;



typedef struct s_resource {
	t_data	canvas;
	t_block	wall;
	t_block	door;
	int		ceil_color;
	int		floor_color;
}	t_resource;

typedef struct s_game{
	t_player	player;
	t_buttons	buttons;
	t_resource resources;
	void	*mlx;
	void	*win;
	char	**map;
}	t_game;

// INIT
void	init_game(t_game *game);
void	load_imgs(t_game *game);

// PARSE
int		parse_resources(t_game *game, char *file);

// COLOR
int		get_pixel(t_data *data, t_vec point);
int		get_color_shade(int color, double qnt_shade);
int		create_rgb(int r, int g, int b);

// DRAW
void	clean_map(t_game *game);
void	draw_line(t_vec vec1, t_vec vec2, int color, t_game *game);
void	draw_pixel(t_data *data, t_vec vec, int color);
void	draw_square(t_data *canvas, t_vec point, int size, int color);
void	draw_map(t_game *game);

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
int		render_map(t_game *game);
int		update_map(int key_code, t_game *game);

// RAYS
void	raycasting(t_game *game);


// RENDER ENGINE
void	render_engine(t_rays *values, t_game *game);

// RENDER ENGINE UTILS
t_data	*get_direction(t_block *block, t_rays *values);
t_data	*get_texture(t_game *game, t_rays *values);
void	set_perp_wall(t_rays *values, t_game *game);
int		solve_mirroring(int texture, t_rays *values);
double	wall_fabs(float condit, float mult, t_rays *values, t_game *game);





// MOVES
void	kill_window(t_game *game);
void	set_colisions(t_game *game);
void	move_forward(t_game *game);
void	move_back(t_game *game);
void	look_left(t_game *game);
void	look_right(t_game *game);

// UTILS
int		matrix_len(char **matrix);

#endif
