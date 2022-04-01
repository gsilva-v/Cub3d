#include <cub3d_bonus.h>

int	get_previous_wall_x(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y][(int)game->player.pos.x - index] && \
		game->map[(int)game->player.pos.y][(int)game->player.pos.x - index] != WALL)
		index--;
	return (index);
}

int	get_previous_wall_y(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y - index] && \
		game->map[(int)game->player.pos.y - index][(int)game->player.pos.x] && \
		game->map[(int)game->player.pos.y - index][(int)game->player.pos.x] != WALL)
		index--;
	return (index);
}

int	get_next_wall_y(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y + index] && \
	game->map[(int)game->player.pos.y + index][(int)game->player.pos.x] \
	&& game->map[(int)game->player.pos.y + index][(int)game->player.pos.x] != WALL)
		index++;
	return (index);
}

int	get_next_wall_x(t_game *game)
{
	int	index;

	index = 0;
	while (game->map[(int)game->player.pos.y] && game->map[(int)game->player.pos.y][(int)game->player.pos.x + \
	index] && game->map[(int)game->player.pos.y][(int)game->player.pos.x + \
	index] != WALL)
		index++;
	return (index);
}

int test_previous_y(t_game *game, t_vec map_pos, t_vec velocity)
{
	if (!(map_pos.y > get_previous_wall_y(game)))
		return (0);
	if (!(game->map[(int)(game->player.pos.y + velocity.y * 1.0f)]))
		return (0);
	if (!(game->map[(int)(game->player.pos.y + velocity.y * 1.0f)][(int)game->player.pos.x]))
		return (0);
	if (!(ft_char_in_set(game->map[(int)(game->player.pos.y + velocity.y *1.0f)][(int)game->player.pos.x], "03")))
		return (0);
	return (1);
}

int test_previous_x(t_game *game, t_vec map_pos, t_vec velocity)
{
	if (!(map_pos.x > get_previous_wall_x(game)))
		return (0);
	if (!(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + velocity.x * 1.0f)]))
		return (0);
	if (!(ft_char_in_set(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + velocity.x * 1.0f)], "03")))
		return (0);
	return (1);
}

void	handle_previous_wall(t_game *game, t_vec map_pos, t_vec velocity)
{
	if (test_previous_x(game, map_pos, velocity))
		move_cam_x(game, velocity);
	if (test_previous_y(game, map_pos, velocity))
		move_cam_y(game, velocity);
}

int test_next_x(t_game *game, t_vec map_pos, t_vec velocity)
{
	if(!(map_pos.x < get_next_wall_x(game)))
		return (0);
	if(!(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + velocity.x * 1.0f)]))
		return (0);
	if(!ft_char_in_set(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + velocity.x * 1.0f)], "03"))
		return (0);
	return (1);
}

int test_next_y(t_game *game, t_vec map_pos, t_vec velocity)
{
	if(!(map_pos.y < get_next_wall_y(game)))
		return(0);
	if(!(game->map[(int)(game->player.pos.y + velocity.y * 1.0f)]))
		return(0);
	if(!(game->map[(int)(game->player.pos.y + velocity.y * 1.0f)][(int)game->player.pos.x]))
		return(0);
	if(!ft_char_in_set(game->map[(int)(game->player.pos.y + velocity.y * 1.0f)][(int)game->player.pos.x], "03"))
		return(0);
	return(1);
}


void	handle_next_wall(t_game *game, t_vec map_pos, t_vec velocity)
{
	if (test_next_x(game, map_pos, velocity))
		move_cam_x(game, velocity);
	if (test_next_y(game, map_pos, velocity))
		move_cam_y(game, velocity);
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
	map_pos.x = ((velocity.x * 1.0f));
	map_pos.y = ((velocity.y * 1.0f));
	if (game->buttons.down)
	{
		if (game->player.pos.x + map_pos.x > 0 && \
			ft_char_in_set(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + map_pos.x)], "03"))
			move_cam_x(game, map_pos);
		if (game->player.pos.y + map_pos.y > 0 && \
			ft_char_in_set(game->map[(int)(game->player.pos.y + map_pos.y)][(int)game->player.pos.x], "03"))
			move_cam_y(game, map_pos);
	}
	else if (game->buttons.up)
	{
		if (game->player.pos.x + map_pos.x < get_higher_len(game->map) && \
			ft_char_in_set(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + map_pos.x)], "03"))
			move_cam_x(game, map_pos);
		if (game->player.pos.y + map_pos.y < matrix_len(game->map) && \
			ft_char_in_set(game->map[(int)(game->player.pos.y + map_pos.y)][(int)game->player.pos.x], "03"))
			move_cam_y(game, map_pos);
	}
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
	map_pos.x = ((strafe_vel.x * 1.0f));
	map_pos.y = ((strafe_vel.y * 1.0f));
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
