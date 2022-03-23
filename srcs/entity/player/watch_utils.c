#include <cub3d.h>

void	change_direction(t_game *game, float rot_speed)
{
	double oldDirX;

	oldDirX = game->player.direction.x;
	game->player.direction.x = game->player.direction.x * \
	cos(rot_speed) - game->player.direction.y * sin(rot_speed);
	game->player.direction.y = oldDirX * sin(rot_speed) + \
	game->player.direction.y * cos(rot_speed);
}

void	change_plane(t_game *game, float rot_speed)
{
    double oldPlaneX;

	oldPlaneX = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(rot_speed) - \
	game->player.plane.y * sin(rot_speed);
	game->player.plane.y = oldPlaneX * sin(rot_speed) + \
	game->player.plane.y * cos(rot_speed);
}
