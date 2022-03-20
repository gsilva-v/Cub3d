#include <ray.h>

int	game_update(int keycode, t_game *game)
{
	if(keycode == 'a')
		game->keyHandler.up = TRUE;
	if(keycode == 's')
		game->keyHandler.down = TRUE;
	if(keycode == 'a')
		game->keyHandler.left = TRUE;
	if(keycode == 'd')
		game->keyHandler.right = TRUE;
	//player_update(keycode, game);
}
