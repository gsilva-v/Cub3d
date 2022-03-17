#include <cub3d.h>

extern t_vec player;

extern char map[8][8];

float get_dist(t_game *datas, t_vec final_point)
{
	return (sqrt((datas->player.x - final_point.x) * (datas->player.x - final_point.x) + (datas->player.y - final_point.y) * (datas->player.y - final_point.y)));
}

float	check_valid_pi(float num)
{
	if (num < 0)
		num += 2 * PI;
	if (num > 2 * PI)
		num -= 2 * PI;
	return (num);
}

t_rays init_values(t_game *datas)
{
	t_rays aux;

	ft_bzero(&aux, sizeof(t_rays));
	aux.ray_angle = datas->player_angle - DR * 30;
	aux.ray_angle = check_valid_pi(aux.ray_angle);
	aux.disH = 1000000;
	aux.disV = 1000000;
	
	return (aux);
}

void	set_rays_horizontal(t_rays *values, t_game *datas)
{
	values->horizontal_x = values->ray_x;
	values->horizontal_y = values->ray_y;
	values->a_tan = -1/tan(values->ray_angle);
	if (values->ray_angle > PI)
	{
		values->ray_y =(((int)datas->player.y >> 6) << 6) - 0.0001f;
		values->ray_x = (datas->player.y - values->ray_y) * values->a_tan + datas->player.x;
		values->y_offset = -64;
		values->x_offset = -values->y_offset * values->a_tan;
	}
	else if (values->ray_angle < PI)
	{
		values->ray_y =(((int)datas->player.y >> 6) << 6) + 64;
		values->ray_x = (datas->player.y - values->ray_y) * values->a_tan + datas->player.x;
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
		
		if ((values->map_x < 8 && values->map_y < 8 && values->map_x >= 0  && values->map_y >= 0) && map[values->map_y][values->map_x] == 1)
		{
			values->horizontal_x = values->ray_x;
			values->horizontal_y = values->ray_y;
			values->disH = get_dist(datas, (t_vec){.x = values->ray_x, .y = values->ray_y});
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
		values->ray_x =(((int)datas->player.x >> 6) << 6) - 0.0001f;
		values->ray_y = (datas->player.x - values->ray_x) * values->n_tan + datas->player.y;
		values->x_offset = -64;
		values->y_offset = -values->x_offset * values->n_tan;
	}
	if (values->ray_angle < P2 || values->ray_angle > P3)
	{
		values->ray_x =(((int)datas->player.x >> 6) << 6) + 64;
		values->ray_y = (datas->player.x - values->ray_x) * values->n_tan + datas->player.y;
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
		
		if ((values->map_x < 8 && values->map_y < 8 && values->map_x >=0  && values->map_y >= 0) && map[values->map_y][values->map_x] == 1)
		{
			values->vertical_x = values->ray_x;
			values->vertical_y = values->ray_y;
			values->disV = get_dist(datas, (t_vec){.x = values->ray_x, .y = values->ray_y});
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

void	fix_fisheye(t_rays *values, t_game *datas)
{
	values->cos_angle = datas->player_angle - values->ray_angle;
	values->cos_angle = check_valid_pi(values->cos_angle);
	values->disT = values->disT * cos(values->cos_angle);
}

void	draw_3d(t_rays *values, t_game *datas)
{
	fix_fisheye(values, datas);
	values->lineH = (64 * 320)/values->disT;
	if (values->lineH > 320)
		values->lineH = 320;
	values->line_offset = 160 - values->lineH / 2;

	for (int i = 0; i < 8; i++)
	{
		for(int height = 0; height < values->lineH; height++)
			drawpixel(&datas->canvas, (t_vec){.x = i + values->desloc + (8 * 64), .y = height + values->line_offset}, values->color);
	}
	values->desloc += 8;
}
void	draw_rays(t_game *datas)
{
	t_rays	values;

	values = init_values(datas);
	while (values.rays < 60)
	{
		values.doff = 0;
		set_rays_horizontal(&values, datas);
		set_horizontal_walls(&values, datas);
		values.doff = 0;
		set_rays_vertical(&values, datas);
		set_vertical_walls(&values, datas);
		set_distance(&values);
		drawline((t_vec){.x = datas->player.x + 5, .y = datas->player.y + 5}, \
		(t_vec){.x = values.ray_x, .y = values.ray_y}, 0x00FF00, datas);
		draw_3d(&values, datas);
		values.ray_angle += DR;
		values.ray_angle = check_valid_pi(values.ray_angle);
		values.rays++;
	}
}