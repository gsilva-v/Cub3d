#include <cub3d.h>

void	game_render(t_game *game)
{
	game_update(game);
	player_render(game);
}