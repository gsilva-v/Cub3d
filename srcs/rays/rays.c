#include <cub3d.h>

void	draw_rays(t_game *game)
{
	t_rays	values;

	values = init_values(game);
	while (values.rays < 60)
	{
		values.disH = 1000000;
		values.disV = 1000000;
		values.doff = 0;
		set_rays_horizontal(&values, game);
		set_horizontal_walls(&values, game);
		values.doff = 0;
		set_rays_vertical(&values, game);
		set_vertical_walls(&values, game);
		set_distance(&values);
		draw_line((t_vec){.x = game->player.x, .y = game->player.y}, \
		(t_vec){.x = values.ray_vec.x, .y = values.ray_vec.y}, 0x00FF00, game);
		draw_3d(&values, game);
		values.ray_angle += DR;
		values.ray_angle = check_valid_pi(values.ray_angle);
		values.rays++;
	}
}
