#include <cub3d.h>

int    create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void	fix_fisheye(t_rays *values, t_game *game)
{
	values->cos_angle = game->player_angle - values->ray_angle;
	values->cos_angle = check_valid_pi(values->cos_angle);
	values->disT = values->disT * cos(values->cos_angle);
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

void	draw_3d(t_rays *values, t_game *game)
{
	int	i;
	int	height;

	i = 0;
	fix_fisheye(values, game);
	values->lineH = (BLOCK_SIZE * 512) / values->disT;
	float text_y_step = 64 / values->lineH;
	float text_y_offset = 0;
	if (values->lineH > 512)
	{
		text_y_offset = (values->lineH - 512) / 2;
		values->lineH = 512;
	}
	values->line_offset = (512 - values->lineH) / 2;
	int pixel;
	float text_y = 0;
	t_int_vec map_pos;

	int y;
	while (i < 8)
	{
		height = 0;
		text_y = text_y_offset * text_y_step;
		while (height < values->lineH)
		{

			map_pos.x = (int)values->ray_vec.x >> 6;
			map_pos.y = (int)values->ray_vec.y >> 6;
			if (game->map[map_pos.y][map_pos.x] == 2)
				pixel = get_pixel(&game->door, (t_vec){.x = values->first_pixel, .y = text_y});
			else 
				pixel = get_pixel(&game->wall, (t_vec){.x = values->first_pixel, .y = text_y});
			pixel = get_color_shade(pixel, values->color);
			draw_pixel(&game->canvas, (t_vec){.x = i + values->desloc + \
			(8 * BLOCK_SIZE), .y = height + values->line_offset }, pixel);
			text_y += text_y_step;
			height++;
		}
		y = values->line_offset + values->lineH;
		while (y < 512)
		{
			draw_pixel(&game->canvas, (t_vec){.x = i + values->desloc + (8 * BLOCK_SIZE), .y = y }, 0x0000F15);//floor
			draw_pixel(&game->canvas, (t_vec){.x = i + values->desloc + (8 * BLOCK_SIZE), .y = 512 - y }, 0xF1400000);//teto
			y++;
		}
		i++;
	}
	values->desloc += game->width;
}