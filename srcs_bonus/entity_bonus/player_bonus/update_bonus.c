#include <cub3d_bonus.h>

void	player_update(t_game *game)
{
	if (game->lose)
		return ;
	watch_rotate(game);
	watch_walk(game);
	watch_strafe(game);
	watch_functions(game);
}
