#include <cub3d.h>

void	player_render(t_game *game)
{
	player_update(game);
	raycasting(game);
}
