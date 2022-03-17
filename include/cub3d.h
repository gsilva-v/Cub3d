#ifndef CUB3D_H
# define CUB3D_H


# include <X11/mlx.h>
# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define BLOCK_SIZE 64
# define ESC 0xff1b
# define PI 3.141592653589f
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vec{
	float	x;
	float	y;
}	t_vec;

typedef struct s_int_vec{
	int	x;
	int	y;
}	t_int_vec;

typedef struct s_rays{
	t_int_vec	map_pos;
	t_vec		ray_vec;
	t_vec		offset;
	t_vec		horizontal;
	t_vec		vertical;
	float		ray_angle;
	float		disT;
	float		disH;
	float		a_tan;
	float		n_tan;
	float		disV;
	float		cos_angle;
	float		lineH;
	float		line_offset;
	int			rays;
	int			doff;
	int			desloc;
	int			color;
}	t_rays;


typedef struct s_game{
	t_data	canvas;
	t_data	wall;
	t_vec	player;
	t_vec	delta_player;
	float	player_angle;
	void	*mlx;
	void	*win;
	int		height;
	int		width;
	int		fov;
	char	map[8][8];
}	t_game;


// DRAW
void	clean_map(t_game *game);
void	drawline(t_vec vec1, t_vec vec2, int color, t_game *datas);
void	drawpixel(t_data *data, t_vec vec, int color);
void	draw_square(t_data *canvas, t_vec point, int size, int color);
void	draw_map(t_game *game);

// RENDER MAP
int		render_map(t_game *datas);
int		update_map(int key_code, t_game *datas);

// RAYS
void	draw_rays(t_game *datas);

// RAYS SETS
void	set_rays_horizontal(t_rays *values, t_game *datas);
void	set_horizontal_walls(t_rays *values, t_game *datas);
void	set_rays_vertical(t_rays *values, t_game *datas);
void	set_vertical_walls(t_rays *values, t_game *datas);
void	set_distance(t_rays *values);

// RAYS UTILS
t_rays	init_values(t_game *datas);
float	get_dist(t_game *datas, t_vec final_point);
float	check_valid_pi(float num);

// UTILS
void	*ft_calloc(size_t nbytes, size_t sizemem);
void	ft_bzero(void *s, size_t n);
#endif
