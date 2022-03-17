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

t_rays *init_values(t_game *datas)
{
	t_rays *aux;

	aux = (t_rays *) ft_calloc (sizeof(t_rays), 1);
	aux->ray_angle = datas->player_angle - DR * 30;
	aux->ray_angle = check_valid_pi(aux->ray_angle);
	aux->a_tan = -1/tan(aux->ray_angle);
	aux->disH = 1000000;
	aux->disV = 1000000;
	
	return (aux);
}


void	draw_rays(t_game *datas)
{
	float ray_angle, ray_x, ray_y, y_offset, x_offset, disT;
	int	 rays, doff = 0, map_x, map_y, desloc = 0, color;
	t_rays	*values;

	values = init_values(datas);
	rays = 0;
	ray_angle = datas->player_angle - DR * 30;
	if (ray_angle < 0)
		ray_angle += 2 * PI;
	if (ray_angle > 2 * PI)
		ray_angle -= 2 * PI;
	while (rays < 60)
	{
		// horizontal
		// printf("%d\n", rays);
		doff = 0;
		float disH = 1000000, horizontal_x = ray_x, horizontal_y = ray_y;
		float a_tan = -1/tan(ray_angle);
		if (ray_angle > PI)
		{
			ray_y =(((int)datas->player.y >> 6) << 6) - 0.0001f;
			ray_x = (datas->player.y - ray_y) * a_tan + datas->player.x;
			y_offset = -64;
			x_offset = -y_offset * a_tan;
		}
		else if (ray_angle < PI)
		{
			ray_y =(((int)datas->player.y >> 6) << 6) + 64;
			ray_x = (datas->player.y - ray_y) * a_tan + datas->player.x;
			y_offset = 64;
			x_offset = -y_offset * a_tan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			ray_x = datas->player.x;
			ray_y = datas->player.y;
			doff = 8;
		}
		while (doff < 8)
		{
			map_x = (int)ray_x >> 6;
			map_y = (int)ray_y >> 6;
			
			if ((map_x < 8 && map_y < 8 && map_x >=0  && map_y >= 0) && map[map_y][map_x] == 1)
			{
				horizontal_x = ray_x;
				horizontal_y = ray_y;
				disH = get_dist(datas, (t_vec){.x = ray_x, .y = ray_y});
				doff = 8;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				doff++;
			}

		}

		//Vertical
		doff = 0;
		float disV = 1000000, vertical_x = ray_x, vertical_y = ray_y;
		float n_tan = -tan(ray_angle);
		if (ray_angle > P2 && ray_angle < P3)
		{
			ray_x =(((int)datas->player.x >> 6) << 6) - 0.0001f;
			ray_y = (datas->player.x - ray_x) * n_tan + datas->player.y;
			x_offset = -64;
			y_offset = -x_offset * n_tan;
		}
		if (ray_angle < P2 || ray_angle > P3)
		{
			ray_x =(((int)datas->player.x >> 6) << 6) + 64;
			ray_y = (datas->player.x - ray_x) * n_tan + datas->player.y;
			x_offset = 64;
			y_offset = -x_offset * n_tan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			ray_x = datas->player.x;
			ray_y = datas->player.y;
			doff = 8;
		}
		while (doff < 8)
		{
			map_x = (int)ray_x >> 6;
			map_y = (int)ray_y >> 6;
			
			if ((map_x < 8 && map_y < 8 && map_x >=0  && map_y >= 0) && map[map_y][map_x] == 1)
			{
				vertical_x = ray_x;
				vertical_y = ray_y;
				disV = get_dist(datas, (t_vec){.x = ray_x, .y = ray_y});
				doff = 8;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				doff++;
			}

		}


		// set distance
		if (disH < disV)
		{
			ray_x = horizontal_x;
			ray_y = horizontal_y;
			disT = disH;
			color = 0xA9A9A9;
		}
		else if (disV < disH)
		{
			ray_x = vertical_x;
			ray_y = vertical_y;
			disT = disV;
			color = 0x808080;
		}
		drawline((t_vec){.x = datas->player.x + 5, .y = datas->player.y + 5}, (t_vec){.x = ray_x, .y = ray_y}, 0x00FF00, datas);
	
	
		// Draw 3D
		// fix curves walls
		float cos_angle = datas->player_angle - ray_angle;
		if (cos_angle < 0)
			cos_angle += 2 * PI;
		if (cos_angle > 2 * PI)
			cos_angle -= 2 * PI;
		disT = disT * cos(cos_angle);


		float lineH = (64 * 320)/disT;
		if (lineH > 320)
			lineH = 320;
		float line_offset = 160 - lineH / 2;

		for (int i = 0; i < 8; i++)
		{
			for(int height = 0; height < lineH; height++)
				drawpixel(&datas->canvas, (t_vec){.x = i + desloc + (8 * 64), .y = height + line_offset}, color);
		}
		desloc += 8;

		ray_angle += DR;
		ray_angle = check_valid_pi(ray_angle);
		// if (ray_angle < 0)
		// 	ray_angle += 2 * PI;
		// if (ray_angle > 2 * PI)
		// 	ray_angle -= 2 * PI;
		rays++;
	}

}