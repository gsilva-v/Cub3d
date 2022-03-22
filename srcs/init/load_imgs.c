#include <cub3d.h>

void	load_imgs(t_game *game)
{
	int trash;
	game->resources.canvas.img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->resources.canvas.addr = mlx_get_data_addr(game->resources.canvas.img, &game->resources.canvas.bits_per_pixel, &game->resources.canvas.line_length, &game->resources.canvas.endian);
	game->resources.wall.img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm", &trash, &trash);
	game->resources.wall.addr = mlx_get_data_addr(game->resources.wall.img, &game->resources.wall.bits_per_pixel, &game->resources.wall.line_length, &game->resources.wall.endian);
	game->resources.door.img = mlx_xpm_file_to_image(game->mlx, "./imgs/door.xpm", &trash, &trash);
	game->resources.door.addr = mlx_get_data_addr(game->resources.door.img, &game->resources.door.bits_per_pixel, &game->resources.door.line_length, &game->resources.door.endian);
}