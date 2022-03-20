#include <ray.h>

int	player_update(t_game *game)
{
	float rotSpeed = 0.1f;


	if(game->keyHandler.right)
		game->player.rotation_speed = rotSpeed;
    else if(game->keyHandler.left)
		game->player.rotation_speed = -rotSpeed;
    else
		game->player.rotation_speed = 0;

	if (game->player.rotation_speed)
	{
		double oldDirX = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(game->player.rotation_speed) - game->player.dir.y * sin(game->player.rotation_speed);
		game->player.dir.y = oldDirX * sin(game->player.rotation_speed) + game->player.dir.y * cos(game->player.rotation_speed);
		double oldPlaneX = game->plane.x;
		game->plane.x = game->plane.x * cos(game->player.rotation_speed) - game->plane.y * sin(game->player.rotation_speed);
		game->plane.y = oldPlaneX * sin(game->player.rotation_speed) + game->plane.y * cos(game->player.rotation_speed);
	}

	if(game->keyHandler.up)
	{
		game->player.velocity = game->player.dir;
		vec_scale(&game->player.velocity, game->player.movement_speed);
	}
    else if(game->keyHandler.down)
    {
		game->player.velocity = game->player.dir;
		vec_scale(&game->player.velocity, -game->player.movement_speed);
    }
    else
	{
		/* if (game->player.velocity.x > 0)
		{
			game->player.velocity.x -= game->player.aceleration.x;
			if (game->player.velocity.x < 0)
				game->player.velocity.x = 0;
		}
		else if (game->player.velocity.x < 0)
		{
			game->player.velocity.x += game->player.aceleration.x;
			if (game->player.velocity.x > 0)
				game->player.velocity.x = 0;
		}

		if (game->player.velocity.y > 0)
		{
			game->player.velocity.y -= game->player.aceleration.y;
			if (game->player.velocity.y < 0)
				game->player.velocity.y = 0;
		}
		else if (game->player.velocity.y < 0)
		{
			game->player.velocity.y += game->player.aceleration.y;
			if (game->player.velocity.y > 0)
				game->player.velocity.y = 0;
		} */
		vec_scale(&game->player.velocity, 0);
	}
	if (game->map[(int)game->player.position.y][(int)(game->player.position.x + game->player.velocity.x * 2.3f)] == 0)
		game->player.position.x += game->player.velocity.x;
	if (game->map[(int)(game->player.position.y + game->player.velocity.y * 2.3f)][(int)game->player.position.x] == 0)
		game->player.position.y += game->player.velocity.y;


	if(game->keyHandler.shoot)
    {
      t_vec position = game->player.position; 
		  position.x += game->player.dir.x * 0.8f;
		  position.y += game->player.dir.y * 0.8f;

		//both camera direction and camera plane must be rotated
		  if (game->map[(int)position.y][(int)position.x] > 1)
        game->map[(int)position.y][(int)position.x] = 0;
    }

}