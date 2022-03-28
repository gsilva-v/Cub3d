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
