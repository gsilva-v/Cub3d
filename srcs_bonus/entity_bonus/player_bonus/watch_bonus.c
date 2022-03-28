#include <cub3d_bonus.h>

void	watch_rotate(t_game *game)
{
	if (game->player.rotate_cam)
	{
		change_direction(game, game->player.rotate_cam * game->elapsed_time);
		change_plane(game, game->player.rotate_cam * game->elapsed_time);
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
		vec_scale(&velocity, movespeed);
	else if (game->buttons.down)
		vec_scale(&velocity, -movespeed);
	else
		vec_scale(&velocity, 0);
	if (ft_char_in_set(game->map[(int)game->player.pos.y][(int)
			(game->player.pos.x + velocity.x * 1.6f)], "03"))
		move_cam_x(game, velocity);
	if (ft_char_in_set(game->map[(int)(game->player.pos.y + velocity.y * \
	1.6f)][(int)game->player.pos.x], "03"))
		move_cam_y(game, velocity);
}

void	watch_strafe(t_game *game)
{
	t_vec	strafe_vel;
	double	old_dir_x;

	strafe_vel = game->player.direction;
	old_dir_x = strafe_vel.x;
	strafe_vel.x = strafe_vel.x * cos(PI / 2) - strafe_vel.y * sin(PI / 2);
	strafe_vel.y = old_dir_x * sin(PI / 2) + strafe_vel.y * cos(PI / 2);
	if (game->buttons.right)
		vec_scale(&strafe_vel, game->player.movespeed * game->elapsed_time);
	else if (game->buttons.left)
		vec_scale(&strafe_vel, -game->player.movespeed * game->elapsed_time);
	else
		vec_scale(&strafe_vel, 0);
	if (ft_char_in_set(game->map[(int)game->player.pos.y][(int)
			(game->player.pos.x + strafe_vel.x * 1.6f)], "03"))
		move_cam_x(game, strafe_vel);
	if (ft_char_in_set(game->map[(int)(game->player.pos.y + \
	strafe_vel.y * 1.6f)][(int)game->player.pos.x], "03"))
		move_cam_y(game, strafe_vel);
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
		{
			game->map[(int)pos.y][(int)pos.x] = OPEN_DOOR;
			game->buttons.function = 0;
		}
		else if (game->map[(int)pos.y][(int)pos.x] == OPEN_DOOR)
		{
			game->map[(int)pos.y][(int)pos.x] = DOOR;
			game->buttons.function = 0;
		}
	}
}
