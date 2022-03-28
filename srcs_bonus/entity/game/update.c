#include <cub3d_bonus.h>

void	game_update(t_game *game)
{
	if (game->buttons.exit)
		finish_him(game, 0);
}
