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
	if (keycode == 65363)//rigth arrow
		game->keyHandler.rotate_right = TRUE;
	if (keycode == 65361)//left arrow
		game->keyHandler.rotate_left = TRUE;
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
	if (keycode == 65363)//rigth arrow
		game->keyHandler.rotate_right = FALSE;
	if (keycode == 65361)//left arrow
		game->keyHandler.rotate_left = FALSE;
}

int	teste(int x, int y, t_game *game)
{
	if (game->last_x)
	{
		if (game->last_x < x) // indo pra direita
		{
			int	diference = x - game->last_x;
			game->keyHandler.rotate_right = 1;
		}
		else //esquerda
		{
			int	diference = game->last_x - x;
			game->keyHandler.rotate_left = 1;
		}
	}
	game->last_x = x;
	fflush(stdout);
}

int	game_run(t_game *game)
{
	mlx_loop_hook(game->server.mlx, game_render, &game->server);
	mlx_hook(game->server.win, KeyPress, KeyPressMask, press_key, game);
	mlx_hook(game->server.win, KeyRelease, KeyReleaseMask, release_key, game);
	mlx_hook(game->server.win, MotionNotify, PointerMotionMask, teste, game);
	mlx_loop(game->server.mlx);
}