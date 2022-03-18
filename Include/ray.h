#ifndef RAY_H
#define RAY_H
#include <mlx.h>
#include <vec.h>
#include <X11/X.h>
#include <math.h>
#include <stdio.h>
#define BLOCK_SIZE 64
#define WIDTH 12
#define HEIGHT 8
#define PI 3.141592653589f
#define P2 PI / 2	
#define P3 3 * PI / 2
#define DR 0.0174533
#define HORIZONTAL 1
#define VERTICAL 2

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_server
{
	void	*mlx;
	void	*win;
	t_data	canvas;
}	t_server;

typedef struct s_player
{
	t_vec	position;
	float	delta_x;
	float	delta_y;
	float	angle;
} t_player;

typedef struct s_game
{
	t_server	server;
	t_player	player;
	t_data		wall;
	t_data		door;
	int			first_pixel;
	char		map[HEIGHT][WIDTH];
}	t_game;

/******
 * 
 *  ENTITIES
 * 
******/
/*
	* GAME
*/
int		game_run(t_game *game);
int		game_update(int keycode, t_game *game);
int		game_render(t_game *game);

/*
	* PLAYER
*/
int		player_update(int keycode, t_game *game);
int		player_render(t_game *game);

/*
	* Rays
*/
void	raycasting(t_game *game);
t_vec	get_vertical_ray(float ray_angle, t_game *game);
t_vec	get_horizontal_ray(float ray_angle, t_game *game);
void	draw_ray(t_game *game, float ray_angle, t_vec ray, int desloc, float color);
int		get_ray(t_vec *ray, float ray_angle, t_game *game);


//Draw
void	drawline(t_vec vec1, t_vec vec2, int color, t_server *server);
int		get_pixel(t_data *data, t_vec point);
void	put_pixel(t_data *data, t_vec point, int color);
void	drawsquare(t_vec point, int size, int color, t_server *server);
void	clear_pixels(t_data *canvas, int width, int height);
void	draw_map(t_game *game);
void	draw_circle(t_vec position, int radius, t_data *data, int color);


//Utils
void	reset_circle(float *radius);

#endif