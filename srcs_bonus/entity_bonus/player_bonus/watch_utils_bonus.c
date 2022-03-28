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
