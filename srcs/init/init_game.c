#include <cub3d.h>

void	init_game(t_game *game)
{
	// game->player = (t_vec){.x = BLOCK_SIZE + 20, .y = BLOCK_SIZE + 20};
	game->player_angle = 0;
	game->width = 8;
	game->height = 8;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, BLOCK_SIZE * (game->height * 2), BLOCK_SIZE * game->width, "RAY");
}