#include <cub3d.h>

void	player_update(t_game *game)
{
	watch_rotate(game);
	watch_walk(game);
	watch_strafe(game);
	watch_functions(game);
}
