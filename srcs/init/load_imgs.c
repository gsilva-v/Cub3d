#include <cub3d.h>

void	load_imgs(t_game *game)
{
	int trash;
	game->resources.canvas.img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->resources.canvas.addr = mlx_get_data_addr(game->resources.canvas.img, &game->resources.canvas.bits_per_pixel, &game->resources.canvas.line_length, &game->resources.canvas.endian);
	game->resources.wall.so.img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm", &trash, &trash);
	game->resources.wall.so.addr = mlx_get_data_addr(game->resources.wall.so.img, &game->resources.wall.so.bits_per_pixel, &game->resources.wall.so.line_length, &game->resources.wall.so.endian);
	game->resources.door.so.img = mlx_xpm_file_to_image(game->mlx, "./imgs/door.xpm", &trash, &trash);
	game->resources.door.so.addr = mlx_get_data_addr(game->resources.door.so.img, &game->resources.door.so.bits_per_pixel, &game->resources.door.so.line_length, &game->resources.door.so.endian);
}