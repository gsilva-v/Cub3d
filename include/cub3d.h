#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../srcs/libs/vec_lib/vec.h"

# define BLOCK_SIZE 64
# define ESC 0xff1b
# define PI 3.141592653589f
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533
# define screenHeight 700
# define screenWidth 1200
# define FLOOR 0
# define WALL 1
# define DOOR 2

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
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_colisions{
	t_vec	offset;
	t_int_vec ip;
	t_int_vec ip_add_offset;
	t_int_vec ip_sub_offset;
}	t_colisions;

typedef struct s_rays{
	t_int_vec	map_pos;
	t_vec		ray_dir;
	t_vec		camera_pixel;
	double		multiplier;
	double		dlt_x;
	double		dlt_y;
	double		dst_x;
	double		dst_y;
	double		perp_wall;
	float		color;
	float		first_pixel;
	int			line_height;
	int			start_line;
	int			end_line;
	int			rays;
	int			hit_side;
	int			step_x;
	int			step_y;
}	t_rays;

typedef struct s_game{
	t_colisions	colisions;
	t_data	canvas;
	t_data	wall;
	t_data	door;
	t_vec	player;
	t_vec	delta_player;
	t_vec		plane;
	t_vec		direction;
	t_buttons buttons;
	float	player_angle;
	void	*mlx;
	void	*win;
	int		height;
	int		width;
	int		fov;
	char	map[8][8];
}	t_game;

// INIT
void	init_game(t_game *game);
void	load_imgs(t_game *game);

// 3D
void	draw_3d(t_rays *values, t_game *game);
int		get_pixel(t_data *data, t_vec point);

// DRAW
void	clean_map(t_game *game);
void	draw_line(t_vec vec1, t_vec vec2, int color, t_game *game);
void	draw_pixel(t_data *data, t_vec vec, int color);
void	draw_square(t_data *canvas, t_vec point, int size, int color);
void	draw_map(t_game *game);

// RENDER MAP
int		render_map(t_game *game);
int		update_map(int key_code, t_game *game);

// RAYS
void	raycasting(t_game *game);

// RAYS SETS


// RAYS UTILS
t_rays	init_values(t_game *game);


// MOVES
void	kill_window(t_game *game);
void	set_colisions(t_game *game);
void	move_forward(t_game *game);
void	move_back(t_game *game);
void	look_left(t_game *game);
void	look_right(t_game *game);

// UTILS
void	*ft_calloc(size_t nbytes, size_t sizemem);
void	ft_bzero(void *s, size_t n);

#endif
