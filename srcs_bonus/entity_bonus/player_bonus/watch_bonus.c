#include <cub3d_bonus.h>

int	get_previous_wall_x(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y][(int)game->player.pos.x - index]
	!= WALL)
		index--;
	return (index);
}

int	get_previous_wall_y(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y - index][(int)game->player.pos.x]
		!= WALL)
		index--;
	return (index);
}

int	get_next_wall_y(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y + index][(int)game->player.pos.x]
		!= WALL)
		index++;
	return (index);
}

int	get_next_wall_x(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y][(int)game->player.pos.x + \
	index] != WALL)
		index++;
	return (index);
}

void	handle_previous_wall(t_game *game, t_vec map_pos, t_vec velocity)
{
	t_vec	pos;

	pos = game->player.pos;
	pos.x -= 1;
	while (pos.x >= 0 && pos.x >= velocity.x + game->player.pos.x && game->map[(int)game->player.pos.y][(int)(pos.x)])
	{
		if (ft_char_in_set(game->map[(int)game->player.pos.y][(int)(pos.x)], "03"))
		{
			move_cam_x(game, velocity);
			break ;
		}
		pos.x -= 1;
	}
	pos = game->player.pos;
	pos.y -= 1;
	while (pos.y >= 0 && pos.y >= velocity.y + game->player.pos.y && game->map[(int)pos.y][(int)(game->player.pos.x)])
	{
		if (ft_char_in_set(game->map[(int)pos.y][(int)(game->player.pos.x)], "03"))
		{
			move_cam_y(game, velocity);
			break ;
		}
		pos.y -= 1;
	}
}

void	handle_next_wall(t_game *game, t_vec map_pos, t_vec velocity)
{
	t_vec	pos;

	pos = game->player.pos;
	pos.x += 1;
	while (pos.x <= velocity.x + game->player.pos.x && game->map[(int)game->player.pos.y][(int)(pos.x)])
	{
		if (ft_char_in_set(game->map[(int)game->player.pos.y][(int)(pos.x)], "03"))
		{
			move_cam_x(game, velocity);
			break ;
		}
		pos.x += 1;
	}
	pos = game->player.pos;
	pos.y += 1;
	while (pos.y <= velocity.y + game->player.pos.y && game->map[(int)pos.y][(int)(game->player.pos.x)])
	{
		if (ft_char_in_set(game->map[(int)pos.y][(int)(game->player.pos.x)], "03"))
		{
			move_cam_y(game, velocity);
			break ;
		}
		pos.y += 1;
	}
}

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
	t_vec	map_pos;

	movespeed = game->player.movespeed * game->elapsed_time;
	velocity = game->player.direction;
	if (game->buttons.up)
		vec_scale(&velocity, movespeed);
	else if (game->buttons.down)
		vec_scale(&velocity, -movespeed);
	else
		vec_scale(&velocity, 0);
	map_pos.x = ((velocity.x * 1.6f));
	map_pos.y = ((velocity.y * 1.6f));
	if (game->buttons.down)
		handle_next_wall(game, map_pos, velocity);
	else if (game->buttons.up)
		handle_previous_wall(game, map_pos, velocity);
}

void	watch_strafe(t_game *game)
{
	t_vec	strafe_vel;
	double	old_dir_x;
	t_vec	map_pos;

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
	map_pos.x = ((strafe_vel.x * 1.6f));
	map_pos.y = ((strafe_vel.y * 1.6f));
	if (game->buttons.right)
		handle_next_wall(game, map_pos, strafe_vel);
	else if (game->buttons.left)
		handle_previous_wall(game, map_pos, strafe_vel);
}

void	watch_functions(t_game *game)
{
	t_vec	pos;

	if (game->buttons.function)
	{
		pos = game->player.pos;
		pos.x += game->player.direction.x * 1.8f;
		pos.y += game->player.direction.y * 1.8f;
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
