#include <ray.h>

int	player_render(t_game *game)
{
	t_vec	final;
	t_vec	initial;

	
	//drawsquare(game->player.position, 10, 0xFF, &game->server);
	player_update(game);

	raycasting(game);
}
