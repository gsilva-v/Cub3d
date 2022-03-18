#include <cub3d.h>

void	set_rays_horizontal(t_rays *values, t_game *game)
{
	values->horizontal.x = game->player.x;
	values->horizontal.y = game->player.y;
	values->a_tan = -1 / tan (values->ray_angle);
	if (values->ray_angle > PI)
	{
		values->ray_vec.y = (((int)game->player.y >> 6) << 6) - 0.0001f;
		values->ray_vec.x = (game->player.y - values->ray_vec.y) * \
		values->a_tan + game->player.x;
		values->offset.y = -BLOCK_SIZE;
		values->offset.x = -values->offset.y * values->a_tan;
	}
	else if (values->ray_angle < PI)
	{
		values->ray_vec.y = (((int)game->player.y >> 6) << 6) + BLOCK_SIZE;
		values->ray_vec.x = (game->player.y - values->ray_vec.y) * \
		values->a_tan + game->player.x;
		values->offset.y = BLOCK_SIZE;
		values->offset.x = -values->offset.y * values->a_tan;
	}
	if (values->ray_angle == 0 || values->ray_angle == PI)
	{
		values->ray_vec.x = game->player.x;
		values->ray_vec.y = game->player.y;
		values->doff = 8;
	}
}

void	set_horizontal_walls(t_rays *values, t_game *game)
{
	while (values->doff < 8)
	{
		// if (values->ray_vec.x && values->ray_vec.y && values->ray_vec.x < game->width * 64 && values->ray_vec.y < game->height * 64)
		// 	draw_pixel(&game->canvas, values->ray_vec, 0xFF0000);
		values->map_pos.x = (int)values->ray_vec.x >> 6;
		values->map_pos.y = (int)values->ray_vec.y >> 6;
		if ((values->map_pos.x < game->height && values->map_pos.y < \
		game->width && values->map_pos.x >= 0 && values->map_pos.y >= 0) && \
		game->map[values->map_pos.y][values->map_pos.x] > 0)
		{
			values->horizontal.x = values->ray_vec.x;
			values->horizontal.y = values->ray_vec.y;
			values->disH = get_dist(game, (t_vec){.x = values->ray_vec.x, \
			.y = values->ray_vec.y});
			values->doff = 8;
		}
		else
		{
			values->ray_vec.x += values->offset.x;
			values->ray_vec.y += values->offset.y;
			values->doff += 1;
		}
	}
}

void	set_rays_vertical(t_rays *values, t_game *game)
{

	values->vertical.x = game->player.x;
	values->vertical.y = game->player.y;
	values->n_tan = -tan(values->ray_angle);
	if (values->ray_angle > P2 && values->ray_angle < P3)
	{
		values->ray_vec.x = (((int)game->player.x >> 6) << 6) - 0.0001f;
		values->ray_vec.y = (game->player.x - values->ray_vec.x) \
		* values->n_tan + game->player.y;
		values->offset.x = -BLOCK_SIZE;
		values->offset.y = -values->offset.x * values->n_tan;
	}
	if (values->ray_angle < P2 || values->ray_angle > P3)
	{
		values->ray_vec.x = (((int)game->player.x >> 6) << 6) + BLOCK_SIZE;
		values->ray_vec.y = (game->player.x - values->ray_vec.x) * \
		values->n_tan + game->player.y;
		values->offset.x = BLOCK_SIZE;
		values->offset.y = -values->offset.x * values->n_tan;
	}
	if (values->ray_angle == 0 || values->ray_angle == PI)
	{
		values->ray_vec.x = game->player.x;
		values->ray_vec.y = game->player.y;
		values->doff = 8;
	}
}

void	set_vertical_walls(t_rays *values, t_game *game)
{
	while (values->doff < 8)
	{
		// if (values->ray_vec.x && values->ray_vec.y && values->ray_vec.x < game->width * 64 && values->ray_vec.y < game->height * 64)
		// 	draw_pixel(&game->canvas, values->ray_vec, 0xFF0000);
		values->map_pos.x = (int)values->ray_vec.x >> 6;
		values->map_pos.y = (int)values->ray_vec.y >> 6;
		if ((values->map_pos.x < game->height && values->map_pos.y < \
		game->width && values->map_pos.x >= 0 && values->map_pos.y >= 0) && \
		game->map[values->map_pos.y][values->map_pos.x] > 0)
		{
			values->vertical.x = values->ray_vec.x;
			values->vertical.y = values->ray_vec.y;
			values->disV = get_dist(game, (t_vec){.x = values->ray_vec.x, \
			.y = values->ray_vec.y});
			values->doff = 8;
		}
		else
		{
			values->ray_vec.x += values->offset.x;
			values->ray_vec.y += values->offset.y;
			values->doff += 1;
		}
	}
}

void	set_distance(t_rays *values)
{
	if (values->disH < values->disV)
	{
		values->ray_vec.x = values->horizontal.x;
		values->ray_vec.y = values->horizontal.y;
		values->disT = values->disH;
		values->first_pixel = (int)values->ray_vec.x - (((int)values->ray_vec.x >> 6) << 6);
		values->color = 0.7;
	}
	else if (values->disV < values->disH)
	{
		values->ray_vec.x = values->vertical.x;
		values->ray_vec.y = values->vertical.y;
		values->disT = values->disV;
		values->first_pixel = (int)values->ray_vec.y - (((int)values->ray_vec.y >> 6) << 6);
		values->color = 1;
	}
}
