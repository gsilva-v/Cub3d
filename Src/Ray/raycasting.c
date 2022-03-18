#include <ray.h>

void	raycasting(t_game *game)
{
	t_vec	ray;
	float	ray_angle;
	int		number_of_rays;
	int		desloc = 0;
	float	shade = 1;

	ray_angle = game->player.angle - DR * 30;
	reset_circle(&ray_angle);
	number_of_rays = 0;
	while (number_of_rays < 65)
	{
		ray = (t_vec){0};
		if (get_ray(&ray, ray_angle, game) == HORIZONTAL)
			shade = 0.7f;
		else
			shade = 1.0f;
		if (ray.x && ray.y)
		drawline((t_vec){.x = game->player.position.x, .y=game->player.position.y}, (t_vec){.x=ray.x, .y=ray.y}, 0x00FF00, &game->server);
		draw_ray(game, ray_angle, ray, desloc, shade);
		desloc += 13;
		number_of_rays++;
		ray_angle += DR;
		reset_circle(&ray_angle);
	}
}
