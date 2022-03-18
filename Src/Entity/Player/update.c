#include <ray.h>

int	player_update(int keycode, t_game *game)
{
	float rotSpeed = 0.1f;

	if(keycode == 'd')
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = game->player.dir.x;
      game->player.dir.x = game->player.dir.x * cos(-rotSpeed) - game->player.dir.y * sin(-rotSpeed);
      game->player.dir.y = oldDirX * sin(-rotSpeed) + game->player.dir.y * cos(-rotSpeed);
      double oldPlaneX = game->plane.x;
      game->plane.x = game->plane.x * cos(-rotSpeed) - game->plane.y * sin(-rotSpeed);
      game->plane.y = oldPlaneX * sin(-rotSpeed) + game->plane.y * cos(-rotSpeed);
    }
}