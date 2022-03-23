#include <cub3d.h>

static void	reset_values(t_rays *values, t_player *player)
{
	double multiplier = 2 * values->rays / (double)screenWidth - 1;
	t_vec camera_pixel = player->plane;
	vec_scale(&camera_pixel, multiplier);
	values->ray_dir = player->direction;
	vec_sum(&values->ray_dir, &camera_pixel);
	values->dlt_x = 10000000;
	if (values->ray_dir.x != 0)
		values->dlt_x = fabs(1 / values->ray_dir.x);
	values->dlt_y = 10000000;
	if (values->ray_dir.y != 0)
		values->dlt_y = fabs(1 / values->ray_dir.y);
	
}

static void	check_dist(t_rays *values, t_player *player)
{
	values->map_pos.x = (int)player->pos.x;
	values->map_pos.y = (int)player->pos.y;
	if (values->ray_dir.x < 0)
	{
		values->step_x = -1;
		values->dst_x = (player->pos.x - values->map_pos.x) * values->dlt_x;
	}
	else
	{
		values->step_x = 1;
		values->dst_x = (values->map_pos.x + 1 - player->pos.x) * values->dlt_x;
	}
	if (values->ray_dir.y < 0)
	{
		values->step_y = -1;
		values->dst_y = (player->pos.y - values->map_pos.y) * values->dlt_y;
	}
	else
	{
		values->step_y = 1;
		values->dst_y = (values->map_pos.y + 1 - player->pos.y) * values->dlt_y;
	}
}

static void	dda(t_rays *values, t_game *game)
{
	while (game->map[values->map_pos.y][values->map_pos.x] == FLOOR)
	{
		if (values->dst_x < values->dst_y)
		{
			values->dst_x += values->dlt_x;
			values->map_pos.x += values->step_x;
			values->hit_side = 0; //parede vertical
		}
		else
		{
			values->dst_y += values->dlt_y;
			values->map_pos.y += values->step_y;
			values->hit_side = 1; //parede horizontal
		}
	}
}

void	raycasting(t_game *game)
{
	t_rays values;

	values.rays = 0;
	while (values.rays < screenWidth)
	{
		// reset values
		reset_values(&values, &game->player);
		// calculo de distancias atuais
		check_dist(&values,&game->player);
		// algoritmo DDA
		dda(&values, game);
		// renderização
		render_engine(&values, game);
		// rend(&values, game);
		values.rays++;
	}
}
