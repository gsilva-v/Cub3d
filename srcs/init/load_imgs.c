#include <cub3d.h>

void	load_imgs(t_game *game)
{
	int trash;
	game->canvas.img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->canvas.addr = mlx_get_data_addr(game->canvas.img, &game->canvas.bits_per_pixel, &game->canvas.line_length, &game->canvas.endian);
	game->wall.img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm", &trash, &trash);
	game->wall.addr = mlx_get_data_addr(game->wall.img, &game->wall.bits_per_pixel, &game->wall.line_length, &game->wall.endian);
	game->door.img = mlx_xpm_file_to_image(game->mlx, "./imgs/door.xpm", &trash, &trash);
	game->door.addr = mlx_get_data_addr(game->door.img, &game->door.bits_per_pixel, &game->door.line_length, &game->door.endian);
}
