#include <cub3d.h>

void	set_rays_horizontal(t_rays *values, t_game *datas)
{
	values->horizontal.x = datas->player.x;
	values->horizontal.y = datas->player.y;
	values->a_tan = -1 / tan (values->ray_angle);
	if (values->ray_angle > PI)
	{
		values->ray_vec.y = (((int)datas->player.y >> 6) << 6) - 0.0001f;
		values->ray_vec.x = (datas->player.y - values->ray_vec.y) * \
		values->a_tan + datas->player.x;
		values->offset.y = -BLOCK_SIZE;
		values->offset.x = -values->offset.y * values->a_tan;
	}
	else if (values->ray_angle < PI)
	{
		values->ray_vec.y = (((int)datas->player.y >> 6) << 6) + BLOCK_SIZE;
		values->ray_vec.x = (datas->player.y - values->ray_vec.y) * \
		values->a_tan + datas->player.x;
		values->offset.y = BLOCK_SIZE;
		values->offset.x = -values->offset.y * values->a_tan;
	}
	if (values->ray_angle == 0 || values->ray_angle == PI)
	{
		values->ray_vec.x = datas->player.x;
		values->ray_vec.y = datas->player.y;
		values->doff = 8;
	}
}

void	set_horizontal_walls(t_rays *values, t_game *datas)
{
	while (values->doff < 8)
	{
		values->map_pos.x = (int)values->ray_vec.x >> 6;
		values->map_pos.y = (int)values->ray_vec.y >> 6;
		
		// Provavelmente o bug do raio abrir é aqui
		if ((values->map_pos.x < datas->height && values->map_pos.y < \
		datas->width && values->map_pos.x >= 0 && values->map_pos.y >= 0) && \
		datas->map[values->map_pos.y][values->map_pos.x] == 1)
		{
			values->horizontal.x = values->ray_vec.x;
			values->horizontal.y = values->ray_vec.y;
			values->disH = get_dist(datas, (t_vec){.x = values->ray_vec.x, \
			.y = values->ray_vec.y});
			values->doff = 8;
		}
		else
		{
			values->ray_vec.x += values->offset.x;
			values->ray_vec.y += values->offset.y;
			values->doff++;
		}
	}
}

void	set_rays_vertical(t_rays *values, t_game *datas)
{

	values->vertical.x = datas->player.x;
	values->vertical.y = datas->player.y;
	values->n_tan = -tan(values->ray_angle);
	if (values->ray_angle > P2 && values->ray_angle < P3)
	{
		values->ray_vec.x = (((int)datas->player.x >> 6) << 6) - 0.0001f;
		values->ray_vec.y = (datas->player.x - values->ray_vec.x) \
		* values->n_tan + datas->player.y;
		values->offset.x = -BLOCK_SIZE;
		values->offset.y = -values->offset.x * values->n_tan;
	}
	if (values->ray_angle < P2 || values->ray_angle > P3)
	{
		values->ray_vec.x = (((int)datas->player.x >> 6) << 6) + BLOCK_SIZE;
		values->ray_vec.y = (datas->player.x - values->ray_vec.x) * \
		values->n_tan + datas->player.y;
		values->offset.x = BLOCK_SIZE;
		values->offset.y = -values->offset.x * values->n_tan;
	}
	if (values->ray_angle == 0 || values->ray_angle == PI)
	{
		values->ray_vec.x = datas->player.x;
		values->ray_vec.y = datas->player.y;
		values->doff = 8;
	}
}

void	set_vertical_walls(t_rays *values, t_game *datas)
{
	while (values->doff < 8)
	{
		values->map_pos.x = (int)values->ray_vec.x >> 6;
		values->map_pos.y = (int)values->ray_vec.y >> 6;
		if ((values->map_pos.x < datas->height && values->map_pos.y < \
		datas->width && values->map_pos.x >= 0 && values->map_pos.y >= 0) && \
		datas->map[values->map_pos.y][values->map_pos.x] == 1)
		{
			values->vertical.x = values->ray_vec.x;
			values->vertical.y = values->ray_vec.y;
			values->disV = get_dist(datas, (t_vec){.x = values->ray_vec.x, \
			.y = values->ray_vec.y});
			values->doff = 8;
		}
		else
		{
			values->ray_vec.x += values->offset.x;
			values->ray_vec.y += values->offset.y;
			values->doff++;
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
		values->color = 0xA9A9A9;
	}
	else if (values->disV < values->disH)
	{
		values->ray_vec.x = values->vertical.x;
		values->ray_vec.y = values->vertical.y;
		values->disT = values->disV;
		values->color = 0x808080;
	}
}
