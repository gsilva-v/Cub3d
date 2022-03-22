#include <cub3d.h>

void	player_update(t_game *game)
{
	// rotação
	float rot_speed;
	if (game->buttons.rotate_right)
		rot_speed = 0.1f;
	else if (game->buttons.rotate_left)
		rot_speed = -0.1f;
	else
		rot_speed = 0;
	if (game->buttons.rotate_left && game->buttons.rotate_right)
		rot_speed = 0;
	if (rot_speed)
	{
		double oldDirX = game->player.direction.x;
        game->player.direction.x = game->player.direction.x * cos(rot_speed) - game->player.direction.y * sin(rot_speed);
        game->player.direction.y = oldDirX * sin(rot_speed) + game->player.direction.y * cos(rot_speed);
        double oldPlaneX = game->player.plane.x;
        game->player.plane.x = game->player.plane.x * cos(rot_speed) - game->player.plane.y * sin(rot_speed);
        game->player.plane.y = oldPlaneX * sin(rot_speed) + game->player.plane.y * cos(rot_speed);
	}

// andar pra frente e pra tras
	t_vec velocity = game->player.direction;

	if (game->buttons.up)
		vec_scale(&velocity, 0.1f);
	else if (game->buttons.down)
		vec_scale(&velocity, -0.1f);
	else
		vec_scale(&velocity, 0);
	if (game->map[(int)game->player.pos.y][(int)(game->player.pos.x + velocity.x * 5)] == FLOOR)
		game->player.pos.x += velocity.x;
	if (game->map[(int)(game->player.pos.y + velocity.y * 5)][(int)game->player.pos.x] == FLOOR)
		game->player.pos.y += velocity.y;

// strafe (andar de lado)
	t_vec strafe_velocity = game->player.direction;

	double oldDirX = strafe_velocity.x;
    strafe_velocity.x = strafe_velocity.x * cos(PI / 2) - strafe_velocity.y * sin(PI / 2);
    strafe_velocity.y = oldDirX * sin(PI / 2) + strafe_velocity.y * cos(PI / 2);
	if (game->buttons.right)
		vec_scale(&strafe_velocity, 0.1f);
	else if (game->buttons.left)
		vec_scale(&strafe_velocity, -0.1f);
	else
		vec_scale(&strafe_velocity, 0);
	if (game->map[(int)game->player.pos.y][(int)(game->player.pos.x + strafe_velocity.x * 5)] == FLOOR)
		game->player.pos.x += strafe_velocity.x;
	if (game->map[(int)(game->player.pos.y + strafe_velocity.y * 5)][(int)game->player.pos.x] == FLOOR)
		game->player.pos.y += strafe_velocity.y;

// funçoes

	if (game->buttons.function)
	{
		t_vec pos = game->player.pos;
		pos.x += game->player.direction.x * 0.8;
		pos.y += game->player.direction.y * 0.8;
		if (game->map[(int)pos.y][(int)pos.x] == DOOR)
			game->map[(int)pos.y][(int)pos.x] = FLOOR;
	} 
}
