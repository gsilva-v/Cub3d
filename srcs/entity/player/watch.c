#include <cub3d.h>

void	watch_rotate(t_game *game)
{
	if (game->player.rotate_cam)
	{
		change_direction(game, game->player.rotate_cam);
		change_plane(game, game->player.rotate_cam);
		game->player.rotate_cam = 0;
	}
}

void	watch_walk(t_game *game)
{
	t_vec	velocity;
	float	movespeed;


	movespeed = game->player.movespeed * game->elapsed_time;
	velocity = game->player.direction;
	if (game->buttons.up)
	{
		// printf("%f\n", movespeed);
		// exit(0);
		vec_scale(&velocity, movespeed);
	}
	else if (game->buttons.down)
		vec_scale(&velocity, -movespeed);
	else
		vec_scale(&velocity, 0);
	if (game->map[(int)game->player.pos.y][(int)(game->player.pos.x + \
	velocity.x * 5)] == FLOOR)
		game->player.pos.x += velocity.x;
	if (game->map[(int)(game->player.pos.y + velocity.y * \
	5)][(int)game->player.pos.x] == FLOOR)
		game->player.pos.y += velocity.y;
}

void	watch_strafe(t_game *game)
{
	t_vec	strafe_velocity;
	double	old_dir_x;

	strafe_velocity = game->player.direction;
	old_dir_x = strafe_velocity.x;
	strafe_velocity.x = strafe_velocity.x * cos(PI / 2) - \
	strafe_velocity.y * sin(PI / 2);
	strafe_velocity.y = old_dir_x * sin(PI / 2) + strafe_velocity.y * \
	cos(PI / 2);
	if (game->buttons.right)
		vec_scale(&strafe_velocity, game->player.movespeed);
	else if (game->buttons.left)
		vec_scale(&strafe_velocity, -game->player.movespeed);
	else
		vec_scale(&strafe_velocity, 0);
	if (game->map[(int)game->player.pos.y][(int)(game->player.pos.x + \
	strafe_velocity.x * 5)] == FLOOR)
		game->player.pos.x += strafe_velocity.x;
	if (game->map[(int)(game->player.pos.y + strafe_velocity.y * \
	5)][(int)game->player.pos.x] == FLOOR)
		game->player.pos.y += strafe_velocity.y;
}

void	watch_functions(t_game *game)
{
	t_vec	pos;

	if (game->buttons.function)
	{
		pos = game->player.pos;
		pos.x += game->player.direction.x * 0.8;
		pos.y += game->player.direction.y * 0.8;
		if (game->map[(int)pos.y][(int)pos.x] == DOOR)
			game->map[(int)pos.y][(int)pos.x] = FLOOR;
	}
}
