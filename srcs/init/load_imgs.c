#include <cub3d.h>

void	load_imgs(t_game *game)
{
	int trash;
	game->resources.canvas.img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->resources.canvas.addr = mlx_get_data_addr(game->resources.canvas.img, &game->resources.canvas.bits_per_pixel, &game->resources.canvas.line_length, &game->resources.canvas.endian);

	game->resources.wall.no.img = mlx_xpm_file_to_image(game->mlx, game->resources.wall.no.name, &trash, &trash);
	game->resources.wall.no.addr = mlx_get_data_addr(game->resources.wall.no.img, &game->resources.wall.no.bits_per_pixel, &game->resources.wall.no.line_length, &game->resources.wall.no.endian);
	
	game->resources.wall.so.img = mlx_xpm_file_to_image(game->mlx, game->resources.wall.so.name, &trash, &trash);
	game->resources.wall.so.addr = mlx_get_data_addr(game->resources.wall.so.img, &game->resources.wall.so.bits_per_pixel, &game->resources.wall.so.line_length, &game->resources.wall.so.endian);
	
	game->resources.wall.we.img = mlx_xpm_file_to_image(game->mlx, game->resources.wall.we.name, &trash, &trash);
	game->resources.wall.we.addr = mlx_get_data_addr(game->resources.wall.we.img, &game->resources.wall.we.bits_per_pixel, &game->resources.wall.we.line_length, &game->resources.wall.we.endian);
	
	game->resources.wall.ea.img = mlx_xpm_file_to_image(game->mlx, game->resources.wall.ea.name, &trash, &trash);
	game->resources.wall.ea.addr = mlx_get_data_addr(game->resources.wall.ea.img, &game->resources.wall.ea.bits_per_pixel, &game->resources.wall.ea.line_length, &game->resources.wall.ea.endian);
	
	game->resources.door.so.img = mlx_xpm_file_to_image(game->mlx, "./imgs/door.xpm", &trash, &trash);
	game->resources.door.so.addr = mlx_get_data_addr(game->resources.door.so.img, &game->resources.door.so.bits_per_pixel, &game->resources.door.so.line_length, &game->resources.door.so.endian);
	
	game->resources.door.no.img = mlx_xpm_file_to_image(game->mlx, "./imgs/door.xpm", &trash, &trash);
	game->resources.door.no.addr = mlx_get_data_addr(game->resources.door.no.img, &game->resources.door.no.bits_per_pixel, &game->resources.door.no.line_length, &game->resources.door.no.endian);
	
	game->resources.door.we.img = mlx_xpm_file_to_image(game->mlx, "./imgs/door.xpm", &trash, &trash);
	game->resources.door.we.addr = mlx_get_data_addr(game->resources.door.we.img, &game->resources.door.we.bits_per_pixel, &game->resources.door.we.line_length, &game->resources.door.we.endian);
	
	game->resources.door.ea.img = mlx_xpm_file_to_image(game->mlx, "./imgs/door.xpm", &trash, &trash);
	game->resources.door.ea.addr = mlx_get_data_addr(game->resources.door.ea.img, &game->resources.door.ea.bits_per_pixel, &game->resources.door.ea.line_length, &game->resources.door.ea.endian);

}