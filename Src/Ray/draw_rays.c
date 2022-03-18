#include <ray.h>

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_color_shade(int color, double qnt_shade)
{
	int	r;
	int	g;
	int	b;

	r = ((color & (0xFF << 16)) >> 16) * qnt_shade;
	g = ((color & (0xFF << 8)) >> 8) * qnt_shade;
	b = (color & 0xFF) * qnt_shade;
	return (create_rgb(r, g, b));
}

void	draw_ray(t_game *game, float ray_angle, t_vec ray, int desloc, float shade)
{
	int	width;
	int	height;

	width = 0;
	/*Fixing fish Eyes*/
	float	ca = game->player.angle - ray_angle;
		if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	ray.magnitude = ray.magnitude * cos(ca);
	
	float	lineH = (BLOCK_SIZE * 512) / ray.magnitude;
	float	texture_step = 64 / lineH;
	float	texture_offset = 0;
	if (lineH > 512)//line height
	{
		texture_offset = (lineH - 512) / 2;
		lineH = 512;
	}
	float	lineO = (512 - lineH) / 2;
	float	texture_y;
	int	pixel;
	float	texture_desloc = 0;;
	static t_vec		previous_ray;
	/* if (previous_ray.x && previous_ray.y)
	{
		if (previous_ray.direction == ray.direction)
		{
			if ((ray.direction == VERTICAL && (int)ray.x == (int) previous_ray.x) || (ray.direction == HORIZONTAL && (int)ray.y == (int) previous_ray.y))
			{
				if (ray.first_pixel < previous_ray.first_pixel)
					ray.first_pixel = previous_ray.first_pixel;
				printf("here\n");
			}
		}
	} */

	//draw walls
	while (width < 13)
	{
		height = 0;
		texture_y = texture_offset* texture_step;
		
		while (height < lineH)
		{
			t_ivec	map_pos;

			map_pos.x = ((int)ray.x >> 6); 
			map_pos.y = ((int)ray.y >> 6);
			if (game->map[map_pos.y][map_pos.x] == 2)
				pixel = get_pixel(&game->door, (t_vec){.x = ray.first_pixel, .y = texture_y});
			else
				pixel = get_pixel(&game->wall, (t_vec){.x = ray.first_pixel, .y = texture_y});
			pixel = get_color_shade(pixel, shade);
			put_pixel(&game->server.canvas, (t_vec){.x= width + desloc + (WIDTH * 64), .y= height + lineO}, pixel);
			texture_y += texture_step;
			height++;
		}
		if (game->first_pixel + texture_desloc < 64)
			texture_desloc += 0.5f;
		width++;
	}

	//draw floors
	width = 0;
	while (width < 13)
	{
		for(int y  = lineO + lineH; y < 512; y++)
		{
			put_pixel(&game->server.canvas, (t_vec) {.x = width + desloc + (WIDTH * 64), .y = y}, 0x0000F15);
			put_pixel(&game->server.canvas, (t_vec) {.x = width + desloc + (WIDTH * 64), .y = 512 - y}, 0xF1400000);
		}
		width++;
	}
}