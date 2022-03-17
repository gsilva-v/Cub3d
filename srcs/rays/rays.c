#include <cub3d.h>

void	fix_fisheye(t_rays *values, t_game *datas)
{
	values->cos_angle = datas->player_angle - values->ray_angle;
	values->cos_angle = check_valid_pi(values->cos_angle);
	values->disT = values->disT * cos(values->cos_angle);
}

void	draw_3d(t_rays *values, t_game *datas)
{
	int	i;
	int	height;

	i = 0;
	fix_fisheye(values, datas);
	values->lineH = (BLOCK_SIZE * 320) / values->disT;
	if (values->lineH > 320)
		values->lineH = 320;
	values->line_offset = 240 - values->lineH / 2;
	while (i < 8)
	{
		height = 0;
		while (height < values->lineH)
		{
			drawpixel(&datas->canvas, (t_vec){.x = i + values->desloc + \
			(8 * BLOCK_SIZE), .y = height + values->line_offset }, values->color);
			height++;
		}
		i++;
	}
	values->desloc += datas->width;
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
		(t_vec){.x = values.ray_vec.x, .y = values.ray_vec.y}, 0x00FF00, datas);
		draw_3d(&values, datas);
		values.ray_angle += DR;
		values.ray_angle = check_valid_pi(values.ray_angle);
		values.rays++;
	}
}
