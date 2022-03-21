#include <cub3d.h>

void	init_game(t_game *game)
{
	game->player_angle = 0;
	game->width = 8;
	game->height = 8;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "RAY");
}