#include <cub3d.h>

extern char map[8][8];

void	set_rays_horizontal(t_rays *values, t_game *datas)
{
	values->horizontal_x = values->ray_x;
	values->horizontal_y = values->ray_y;
	values->a_tan = -1 / tan (values->ray_angle);
	if (values->ray_angle > PI)
	{
		values->ray_y = (((int)datas->player.y >> 6) << 6) - 0.0001f;
		values->ray_x = (datas->player.y - values->ray_y) * values->a_tan + \
		datas->player.x;
		values->y_offset = -64;
		values->x_offset = -values->y_offset * values->a_tan;
	}
	else if (values->ray_angle < PI)
	{
		values->ray_y = (((int)datas->player.y >> 6) << 6) + 64;
		values->ray_x = (datas->player.y - values->ray_y) * values->a_tan + \
		datas->player.x;
		values->y_offset = 64;
		values->x_offset = -values->y_offset * values->a_tan;
	}
	if (values->ray_angle == 0 || values->ray_angle == PI)
	{
		values->ray_x = datas->player.x;
		values->ray_y = datas->player.y;
		values->doff = 8;
	}
}

void	set_horizontal_walls(t_rays *values, t_game *datas)
{
	while (values->doff < 8)
	{
		values->map_x = (int)values->ray_x >> 6;
		values->map_y = (int)values->ray_y >> 6;
		if ((values->map_x < 8 && values->map_y < 8 && values->map_x >= 0 && \
		values->map_y >= 0) && map[values->map_y][values->map_x] == 1)
		{
			values->horizontal_x = values->ray_x;
			values->horizontal_y = values->ray_y;
			values->disH = get_dist(datas, (t_vec){.x = values->ray_x, .y = \
			values->ray_y});
			values->doff = 8;
		}
		else
		{
			values->ray_x += values->x_offset;
			values->ray_y += values->y_offset;
			values->doff++;
		}
	}
}

void	set_rays_vertical(t_rays *values, t_game *datas)
{
	values->vertical_x = values->ray_x;
	values->vertical_y = values->ray_y;
	values->n_tan = -tan(values->ray_angle);
	if (values->ray_angle > P2 && values->ray_angle < P3)
	{
		values->ray_x = (((int)datas->player.x >> 6) << 6) - 0.0001f;
		values->ray_y = (datas->player.x - values->ray_x) * values->n_tan + \
		datas->player.y;
		values->x_offset = -64;
		values->y_offset = -values->x_offset * values->n_tan;
	}
	if (values->ray_angle < P2 || values->ray_angle > P3)
	{
		values->ray_x = (((int)datas->player.x >> 6) << 6) + 64;
		values->ray_y = (datas->player.x - values->ray_x) * values->n_tan + \
		datas->player.y;
		values->x_offset = 64;
		values->y_offset = -values->x_offset * values->n_tan;
	}
	if (values->ray_angle == 0 || values->ray_angle == PI)
	{
		values->ray_x = datas->player.x;
		values->ray_y = datas->player.y;
		values->doff = 8;
	}
}

void	set_vertical_walls(t_rays *values, t_game *datas)
{
	while (values->doff < 8)
	{
		values->map_x = (int)values->ray_x >> 6;
		values->map_y = (int)values->ray_y >> 6;
		if ((values->map_x < 8 && values->map_y < 8 && values->map_x >= 0 && \
		values->map_y >= 0) && map[values->map_y][values->map_x] == 1)
		{
			values->vertical_x = values->ray_x;
			values->vertical_y = values->ray_y;
			values->disV = get_dist(datas, (t_vec){.x = values->ray_x, .y = \
			values->ray_y});
			values->doff = 8;
		}
		else
		{
			values->ray_x += values->x_offset;
			values->ray_y += values->y_offset;
			values->doff++;
		}
	}
}

void	set_distance(t_rays *values)
{
	if (values->disH < values->disV)
	{
		values->ray_x = values->horizontal_x;
		values->ray_y = values->horizontal_y;
		values->disT = values->disH;
		values->color = 0xA9A9A9;
	}
	else if (values->disV < values->disH)
	{
		values->ray_x = values->vertical_x;
		values->ray_y = values->vertical_y;
		values->disT = values->disV;
		values->color = 0x808080;
	}
}
