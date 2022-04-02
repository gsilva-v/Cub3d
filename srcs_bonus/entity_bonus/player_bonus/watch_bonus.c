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

void	handle_cam_y(t_game *game, t_vec map_pos)
{
	t_int_vec	g_pos;

	g_pos.x = (int)(game->player.pos.x + map_pos.x);
	g_pos.y = (int)(game->player.pos.y + map_pos.y);
	if (g_pos.x < get_higher_len(game->map) - 1 && g_pos.x > 0 && \
	game->map[(int)game->player.pos.y] && \
	ft_char_in_set(game->map[(int)game->player.pos.y][(int)
			(game->player.pos.x + map_pos.x)], "03"))
		move_cam_x(game, map_pos);
	if (g_pos.y < matrix_len(game->map) - 1 && g_pos.y > 0 && \
	game->map[g_pos.y] && \
	ft_char_in_set(game->map[g_pos.y][(int)game->player.pos.x], "03"))
		move_cam_y(game, map_pos);
}

void	handle_cam_x(t_game *game, t_vec map_pos)
{
	t_int_vec	g_pos;

	g_pos.x = (int)(game->player.pos.x + map_pos.x);
	g_pos.y = (int)(game->player.pos.y + map_pos.y);
	if (g_pos.x > 0 &&
		g_pos.x < get_higher_len(game->map) - 1 
		&& game->map[(int)game->player.pos.y] && \
		ft_char_in_set(game->map[(int)game->player.pos.y][g_pos.x], "03"))
		move_cam_x(game, map_pos);
	if (g_pos.y > 0 && g_pos.y < matrix_len(game->map) - 1 &&
		game->map[g_pos.y] &&
		ft_char_in_set(game->map[g_pos.y][(int)game->player.pos.x], "03"))
		move_cam_y(game, map_pos);
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
		handle_cam_x(game, map_pos);
	else if (game->buttons.up)
		handle_cam_y(game, map_pos);
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
		handle_cam_x(game, map_pos);
	else if (game->buttons.left)
		handle_cam_y(game, map_pos);
}

void	watch_functions(t_game *game)
{
	t_vec	pos;
	t_vec	pos2;

	if (game->buttons.function)
	{
		pos = game->player.pos;
		pos2 = game->player.pos;
		pos.x += game->player.direction.x;
		pos.y += game->player.direction.y;
		pos2.x += game->player.direction.x *1.4f;
		pos2.y += game->player.direction.y *1.4f;
		if (game->map[(int)pos.y][(int)pos.x] == DOOR || game->map[(int)(pos2.y)][(int)(pos2.x)] == DOOR)
		{
			game->map[(int)pos.y][(int)pos.x] = OPEN_DOOR;
			game->buttons.function = 0;
		}
		else if (game->map[(int)pos.y][(int)pos.x] == OPEN_DOOR || game->map[(int)(pos2.y)][(int)(pos2.x)] == OPEN_DOOR)
		{
			game->map[(int)pos.y][(int)pos.x] = DOOR;
			game->buttons.function = 0;
		}
	}
}
