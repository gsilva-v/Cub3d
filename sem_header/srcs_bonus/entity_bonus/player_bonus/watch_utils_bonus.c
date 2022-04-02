#include <cub3d_bonus.h>

void	change_direction(t_game *game, float rot_speed)
{
	double	old_dir_x;

	old_dir_x = game->player.direction.x;
	game->player.direction.x = game->player.direction.x * \
	cos(rot_speed) - game->player.direction.y * sin(rot_speed);
	game->player.direction.y = old_dir_x * sin(rot_speed) + \
	game->player.direction.y * cos(rot_speed);
}

void	change_plane(t_game *game, float rot_speed)
{
	double	old_plane_x;

	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(rot_speed) - \
	game->player.plane.y * sin(rot_speed);
	game->player.plane.y = old_plane_x * sin(rot_speed) + \
	game->player.plane.y * cos(rot_speed);
}

void	move_cam_y(t_game *game, t_vec velocity)
{
	if (velocity.y > 0)
	{
		if (game->player.pos.y * MBS >= MAP_HEIGHT / 2 && game->map_offset.y \
		+ velocity.y * MBS + MAP_HEIGHT < matrix_len(game->map) * MBS)
			game->map_offset.y += velocity.y * MBS;
	}
	else if (velocity.y < 0)
	{
		if (game->map_offset.y + velocity.y * MBS >= 0)
			game->map_offset.y += velocity.y * MBS;
	}
	game->player.pos.y += velocity.y;
}

void	move_cam_x(t_game *game, t_vec velocity)
{
	if (velocity.x > 0)
	{
		if (game->player.pos.x * MBS >= MAP_WIDTH / 2 && game->map_offset.x \
		+ velocity.x * MBS + MAP_WIDTH < get_higher_len(game->map) * MBS)
			game->map_offset.x += velocity.x * MBS;
	}
	else if (velocity.x < 0)
	{
		if (game->map_offset.x + velocity.x * MBS >= 0)
			game->map_offset.x += velocity.x * MBS;
	}
	game->player.pos.x += velocity.x;
}

void	handle_cam_x(t_game *game, t_vec map_pos)
{
	t_int_vec	g_pos;

	g_pos.x = (int)(game->player.pos.x + map_pos.x);
	g_pos.y = (int)(game->player.pos.y + map_pos.y);
	if (g_pos.x > 0 && g_pos.x < get_higher_len(game->map) - 1
		&& game->map[(int)game->player.pos.y]
		&& ft_char_in_set(game->map[(int)game->player.pos.y][g_pos.x], "03"))
		move_cam_x(game, map_pos);
	if (g_pos.y > 0 && g_pos.y < matrix_len(game->map) - 1
		&& game->map[g_pos.y]
		&& ft_char_in_set(game->map[g_pos.y][(int)game->player.pos.x], "03"))
		move_cam_y(game, map_pos);
}
