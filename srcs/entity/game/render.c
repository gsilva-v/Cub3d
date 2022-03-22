#include <cub3d.h>

int	game_render(t_game *game)
{
	clean_map(game);
	game_update(game);
	player_render(game);
	mlx_put_image_to_window(game->mlx, game->win, game->resources.canvas.img, 0, 0);
}