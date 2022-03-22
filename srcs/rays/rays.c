#include <cub3d.h>

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

void 	reset_values(t_rays *values, t_game *game)
{
	values->multiplier = 2 * values->rays / (double)screenWidth - 1;
	values->camera_pixel = game->plane;
	vec_scale(&values->camera_pixel, values->multiplier);
	values->ray_dir = game->direction;
	vec_sum(&values->ray_dir, &values->camera_pixel);
	values->dlt_x = 10000000;
	if (values->ray_dir.x != 0)
		values->dlt_x = fabs(1/values->ray_dir.x);
	values->dlt_y = 10000000;
	if (values->ray_dir.y != 0)
		values->dlt_y = fabs(1/values->ray_dir.y);
}

void	check_dist(t_rays *values, t_game *game)
{
	values->map_pos.x = (int)game->player.x;
	values->map_pos.y = (int)game->player.y;
	values->step_x = 1;
	values->dst_x = (values->map_pos.x + 1 - game->player.x) * values->dlt_x;
	if (values->ray_dir.x < 0)
	{
		values->step_x = -1;
		values->dst_x = (game->player.x - values->map_pos.x) * values->dlt_x;
	}
	values->step_y = 1;
	values->dst_y = (values->map_pos.y + 1 - game->player.y) * values->dlt_y;
	if (values->ray_dir.y < 0)
	{
		values->step_y = -1;
		values->dst_y = (game->player.y - values->map_pos.y) * values->dlt_y;
	}
}

void	dda(t_rays *values, t_game *game)
{
	while (game->map[values->map_pos.y][values->map_pos.x] == 0)
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

void	render3d(t_rays *values, t_game *game)
{
	if (values->hit_side == 0)
		values->perp_wall = (fabs(values->map_pos.x - game->player.x + ((1 - values->step_x) / 2)) / values->ray_dir.x);
	else
		values->perp_wall = (fabs(values->map_pos.y - game->player.y + ((1 - values->step_y) / 2)) / values->ray_dir.y);
	values->line_height = abs(screenHeight / values->perp_wall);
	values->start_line = -values->line_height / 2 + screenHeight / 2;
	if(values->start_line < 0)
		values->start_line = 0;
	values->end_line = values->line_height / 2 + screenHeight / 2;
	if(values->end_line >= screenHeight)
		values->end_line = screenHeight - 1;
	// values->color = get_color_shade(0xFF0000, 0.7);
	// if (values->hit_side)
	// 	values->color = get_color_shade(values->color, 0.7); 
	double wall_x;	
	if (values->hit_side == 0)
	{
		if (values->ray_dir.x > 0)
			wall_x = fabs(game->player.y + values->perp_wall  * values->ray_dir.y);
		else
			wall_x = fabs(game->player.y - values->perp_wall  * values->ray_dir.y);
	}
	else
	{
		if (values->ray_dir.y > 0)
			wall_x = fabs(game->player.x + values->perp_wall  * values->ray_dir.x);
		else
			wall_x = fabs(game->player.x - values->perp_wall  * values->ray_dir.x);

	}
	wall_x -= floor(wall_x);
	int texture_x = (int)(wall_x * (double)BLOCK_SIZE);
	double step = 1.0 * 64 / values->line_height;
	
	double texture_pos = (values->start_line - screenHeight /2 + values->line_height / 2) * step;
	
	for (int y = values->start_line; y < values->end_line; y++)
	{
		int texture_y = (int)texture_pos & (64 - 1);
		texture_pos += step;
		if (game->map[values->map_pos.y][values->map_pos.x] > 1)
			values->color = get_pixel(&game->door, (t_vec){.x = texture_x, .y = texture_y});
		else
			values->color = get_pixel(&game->wall, (t_vec){.x = texture_x, .y = texture_y});
		if (values->hit_side == 1)
			values->color = get_color_shade(values->color, 0.6);
		draw_pixel(&game->canvas, (t_vec){.x = values->rays, .y = y}, values->color);
	}
}

void raycasting(t_game *game)
{
	t_rays values;

	values = init_values(game);
	while (values.rays < screenWidth)
	{
		// reset values
		reset_values(&values, game);
		// calculo de distancias atuais
		check_dist(&values, game);
		// algoritmo DDA
		dda(&values, game);
		// renderização
		render3d(&values, game);
		values.rays++;
	}
}
