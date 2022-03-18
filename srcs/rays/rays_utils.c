#include <cub3d.h>

float	get_dist(t_game *game, t_vec final_point)
{
	return (sqrt((game->player.x - final_point.x) * \
	(game->player.x - final_point.x) + (game->player.y - final_point.y) * \
	(game->player.y - final_point.y)));
}

float	check_valid_pi(float num)
{
	if (num < 0)
		num += 2 * PI;
	if (num > 2 * PI)
		num -= 2 * PI;
	return (num);
}

t_rays	init_values(t_game *game)
{
	t_rays	aux;

	ft_bzero(&aux, sizeof(t_rays));
	aux.ray_angle = game->player_angle - DR * 30;
	aux.ray_angle = check_valid_pi(aux.ray_angle);
	aux.disH = 1000000;
	aux.disV = 1000000;
	return (aux);
}
