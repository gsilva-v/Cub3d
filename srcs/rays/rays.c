#include <cub3d.h>

static void 	reset_values(t_rays *values, t_player *player)
{
	double multiplier = 2 * values->rays / (double)screenWidth - 1;
	t_vec camera_pixel = player->plane;
	vec_scale(&camera_pixel, multiplier);
	values->ray_dir = player->direction;
	vec_sum(&values->ray_dir, &camera_pixel);
	values->dlt_x = 10000000;
	if (values->ray_dir.x != 0)
		values->dlt_x = fabs(1/values->ray_dir.x);
	values->dlt_y = 10000000;
	if (values->ray_dir.y != 0)
		values->dlt_y = fabs(1/values->ray_dir.y);
	
}

static void	check_dist(t_rays *values, t_player *player)
{
	values->map_pos.x = (int)player->pos.x;
	values->map_pos.y = (int)player->pos.y;
	values->step_x = 1;
	values->dst_x = (values->map_pos.x + 1 - player->pos.x) * values->dlt_x;
	if (values->ray_dir.x < 0)
	{
		values->step_x = -1;
		values->dst_x = (player->pos.x - values->map_pos.x) * values->dlt_x;
	}
	values->step_y = 1;
	values->dst_y = (values->map_pos.y + 1 - player->pos.y) * values->dlt_y;
	if (values->ray_dir.y < 0)
	{
		values->step_y = -1;
		values->dst_y = (player->pos.y - values->map_pos.y) * values->dlt_y;
	}
}

static void	dda(t_rays *values, t_game *game)
{
	while (game->map[values->map_pos.y][values->map_pos.x] == FLOOR)
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

static void	render3d(t_rays *values, t_game *game)
{
	if (values->hit_side == 0)
		values->perp_wall = (fabs(values->map_pos.x - game->player.pos.x + ((1 - values->step_x) / 2)) / values->ray_dir.x);
	else
		values->perp_wall = (fabs(values->map_pos.y - game->player.pos.y + ((1 - values->step_y) / 2)) / values->ray_dir.y);
	int line_height = abs(screenHeight / values->perp_wall);
	int	start_line = -line_height / 2 + screenHeight / 2;
	if(start_line < 0)
		start_line = 0;
	int	end_line = line_height / 2 + screenHeight / 2;
	if(end_line >= screenHeight)
		end_line = screenHeight - 1;
	double wall_x;	
	if (values->hit_side == 0)
	{
		if (values->ray_dir.x > 0)
			wall_x = fabs(game->player.pos.y + values->perp_wall  * values->ray_dir.y);
		else
			wall_x = fabs(game->player.pos.y - values->perp_wall  * values->ray_dir.y);
	}
	else
	{
		if (values->ray_dir.y > 0)
			wall_x = fabs(game->player.pos.x + values->perp_wall  * values->ray_dir.x);
		else
			wall_x = fabs(game->player.pos.x - values->perp_wall  * values->ray_dir.x);
	}
	wall_x -= floor(wall_x);
	int texture_x = (int)(wall_x * (double)BLOCK_SIZE);
	double step = 1.0 * 64 / line_height;
	
	double texture_pos = (start_line - screenHeight /2 + line_height / 2) * step;
	int color;
	for (int y = start_line; y < end_line; y++)
	{
		int texture_y = (int)texture_pos & (64 - 1);
		texture_pos += step;
		if (game->map[values->map_pos.y][values->map_pos.x] == DOOR)
			color = get_pixel(&game->resources.door.so, (t_vec){.x = texture_x, .y = texture_y});
		else
			color = get_pixel(&game->resources.wall.so, (t_vec){.x = texture_x, .y = texture_y});
		if (values->hit_side == 1)
			color = get_color_shade(color, 0.6);
		draw_pixel(&game->resources.canvas, (t_vec){.x = values->rays, .y = y}, color);
	}
}

void	raycasting(t_game *game)
{
	t_rays values;

	values.rays = 0;
	while (values.rays < screenWidth)
	{
		// reset values
		reset_values(&values, &game->player);
		// calculo de distancias atuais
		check_dist(&values,&game->player);
		// algoritmo DDA
		dda(&values, game);
		// renderização
		render3d(&values, game);
		values.rays++;
	}
}
