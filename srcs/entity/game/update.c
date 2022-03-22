#include <cub3d.h>

void	game_update(t_game *game)
{
	// sair
	if (game->buttons.exit)
		kill_window(game);
}