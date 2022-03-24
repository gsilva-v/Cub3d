#include <cub3d.h>

void	game_update(t_game *game)
{
	if (game->buttons.exit)
		finish_him(game, 0);
}
