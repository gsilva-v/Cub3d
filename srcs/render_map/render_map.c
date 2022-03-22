#include <cub3d.h>

int	update( t_game *game)
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
		double oldDirX = game->direction.x;
        game->direction.x = game->direction.x * cos(rot_speed) - game->direction.y * sin(rot_speed);
        game->direction.y = oldDirX * sin(rot_speed) + game->direction.y * cos(rot_speed);
        double oldPlaneX = game->plane.x;
        game->plane.x = game->plane.x * cos(rot_speed) - game->plane.y * sin(rot_speed);
        game->plane.y = oldPlaneX * sin(rot_speed) + game->plane.y * cos(rot_speed);
	}

// andar pra frente e pra tras
	t_vec velocity = game->direction;

	if (game->buttons.up)
		vec_scale(&velocity, 0.1f);
	else if (game->buttons.down)
		vec_scale(&velocity, -0.1f);
	else
		vec_scale(&velocity, 0);
	if (game->map[(int)game->player.y][(int)(game->player.x + velocity.x * 5)] == FLOOR)
		game->player.x += velocity.x;
	if (game->map[(int)(game->player.y + velocity.y * 5)][(int)game->player.x] == FLOOR)
		game->player.y += velocity.y;

// strafe (andar de lado)
	t_vec strafe_velocity = game->direction;

	double oldDirX = strafe_velocity.x;
    strafe_velocity.x = strafe_velocity.x * cos(PI / 2) - strafe_velocity.y * sin(PI / 2);
    strafe_velocity.y = oldDirX * sin(PI / 2) + strafe_velocity.y * cos(PI / 2);
	if (game->buttons.right)
		vec_scale(&strafe_velocity, 0.1f);
	else if (game->buttons.left)
		vec_scale(&strafe_velocity, -0.1f);
	else
		vec_scale(&strafe_velocity, 0);
	if (game->map[(int)game->player.y][(int)(game->player.x + strafe_velocity.x * 5)] == FLOOR)
		game->player.x += strafe_velocity.x;
	if (game->map[(int)(game->player.y + strafe_velocity.y * 5)][(int)game->player.x] == FLOOR)
		game->player.y += strafe_velocity.y;

// funçoes

	if (game->buttons.function)
	{
		t_vec pos = game->player;
		pos.x += game->direction.x * 0.8;
		pos.y += game->direction.y * 0.8;
		if (game->map[(int)pos.y][(int)pos.x] == DOOR)
			game->map[(int)pos.y][(int)pos.x] = 0;
	} 

	// sair
	if (game->buttons.exit)
		kill_window(game);
}

int	render_map(t_game *game)
{
	clean_map(game);
	update(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
}