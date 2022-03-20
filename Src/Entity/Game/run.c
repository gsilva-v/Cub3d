#include <ray.h>

int	press_key(int keycode, t_game *game)
{
	if(keycode == 'w')
		game->keyHandler.up = TRUE;
	if(keycode == 's')
		game->keyHandler.down = TRUE;
	if(keycode == 'a')
		game->keyHandler.left = TRUE;
	if(keycode == 'd')
		game->keyHandler.right = TRUE;
	if (keycode == ' ')
		game->keyHandler.shoot = TRUE;

}

int	release_key(int keycode, t_game *game)
{
	if(keycode == 'w')
		game->keyHandler.up = FALSE;
	if(keycode == 's')
		game->keyHandler.down = FALSE;
	if(keycode == 'a')
		game->keyHandler.left = FALSE;
	if(keycode == 'd')
		game->keyHandler.right = FALSE;
	if (keycode == ' ')
		game->keyHandler.shoot = FALSE;
}


int	game_run(t_game *game)
{
	mlx_loop_hook(game->server.mlx, game_render, &game->server);

	mlx_hook(game->server.win, KeyPress, KeyPressMask, press_key, game);
	mlx_hook(game->server.win, KeyRelease, KeyReleaseMask, release_key, game);
	mlx_loop(game->server.mlx);
}