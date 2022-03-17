#include <cub3d.h>

void	fix_fisheye(t_rays *values, t_game *datas)
{
	values->cos_angle = datas->player_angle - values->ray_angle;
	values->cos_angle = check_valid_pi(values->cos_angle);
	values->disT = values->disT * cos(values->cos_angle);
}


int    create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int    get_color_shade(int color, double qnt_shade)
{
    int    r;
    int    g;
    int    b;

    r = ((color & (0xFF << 16)) >> 16) * qnt_shade;
    g = ((color & (0xFF << 8)) >> 8) * qnt_shade;
    b = (color & 0xFF) * qnt_shade;
    return (create_rgb(r, g, b));
}

void	draw_3d(t_rays *values, t_game *datas)
{
	int	i;
	int	height;

	i = 0;
	fix_fisheye(values, datas);
	values->lineH = (BLOCK_SIZE * 320) / values->disT;
	float text_y_step = 64 / values->lineH;
	float text_y_offset = 0;
	if (values->lineH > 320)
	{
		text_y_offset = (values->lineH - 320) / 2;
		values->lineH = 320;
	}
	values->line_offset = 240 - values->lineH / 2;
	int pixel;
	float text_y = 0;
	t_int_vec map_pos;

	while (i < 8)
	{

		height = 0;
		text_y = text_y_offset * text_y_step;
		while (height < values->lineH)
		{

			map_pos.x = (int)values->ray_vec.x >> 6;
			map_pos.y = (int)values->ray_vec.y >> 6;
			if (datas->map[map_pos.y][map_pos.x] == 2)
				pixel = get_pixel(&datas->door, (t_vec){.x = values->first_pixel, .y = text_y});
			else
				pixel = get_pixel(&datas->wall, (t_vec){.x = values->first_pixel, .y = text_y});
			pixel = get_color_shade(pixel, values->color);
			drawpixel(&datas->canvas, (t_vec){.x = i + values->desloc + \
			(8 * BLOCK_SIZE), .y = height + values->line_offset }, pixel);
			text_y += text_y_step;
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
