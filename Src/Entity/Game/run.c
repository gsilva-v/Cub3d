#include <ray.h>

int	game_run(t_game *game)
{
	mlx_loop_hook(game->server.mlx, game_render, &game->server);
	mlx_hook(game->server.win, KeyPress, KeyPressMask, game_update, game);
	mlx_loop(game->server.mlx);
}