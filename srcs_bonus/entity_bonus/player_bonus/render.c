#include <cub3d_bonus.h>

void	player_render(t_game *game)
{
	player_update(game);
	raycasting(game);
}
