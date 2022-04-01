#include <cub3d_bonus.h>

static void	reset_values(t_rays *values, t_player *player)
{
	double	multiplier;
	t_vec	camera_pixel;

	multiplier = 2 * values->rays / (double)SCREENWIDTH - 1;
	camera_pixel = player->plane;
	vec_scale(&camera_pixel, multiplier);
	values->ray_dir = player->direction;
	vec_sum(&values->ray_dir, &camera_pixel);
	values->dlt_x = 10000000;
	if (values->ray_dir.x != 0)
		values->dlt_x = fabs(1 / values->ray_dir.x);
	values->dlt_y = 10000000;
	if (values->ray_dir.y != 0)
		values->dlt_y = fabs(1 / values->ray_dir.y);
}

static void	check_dist(t_rays *values, t_player *player)
{
	values->map_pos.x = (int)player->pos.x;
	values->map_pos.y = (int)player->pos.y;
	if (values->ray_dir.x < 0)
	{
		values->step_x = -1;
		values->dst_x = (player->pos.x - values->map_pos.x) * values->dlt_x;
	}
	else
	{
		values->step_x = 1;
		values->dst_x = (values->map_pos.x + 1 - player->pos.x) * values->dlt_x;
	}
	if (values->ray_dir.y < 0)
	{
		values->step_y = -1;
		values->dst_y = (player->pos.y - values->map_pos.y) * values->dlt_y;
	}
	else
	{
		values->step_y = 1;
		values->dst_y = (values->map_pos.y + 1 - player->pos.y) * values->dlt_y;
	}
}

void	dda(t_rays *values, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
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
		if (game->map[values->map_pos.y][values->map_pos.x] != FLOOR)
			hit = 1;
	}
}

void	is_on_view(t_game *game, t_entity *entity, t_vec ray_dir)
{
	t_vec	dir_player_entity;

	dir_player_entity = (t_vec){
		.x = entity->pos.x - game->player.pos.x,
		.y = entity->pos.y - game->player.pos.y
	};
	vec_magnitude(&dir_player_entity);
	vec_normalize(&dir_player_entity);
	if (vec_equal(ray_dir, dir_player_entity))
		entity->is_on_view = 1;
}

void	raycasting(t_game *game)
{
	t_rays	values;
	t_vec	ray_dir;

	floor_casting(game);
	values.rays = 0;
	game->ghost.is_on_view = 0;
	game->final.is_on_view = 0;
	while (values.rays < SCREENWIDTH)
	{
		reset_values(&values, &game->player);
		check_dist(&values, &game->player);
		dda(&values, game);
		ray_dir = values.ray_dir;
		vec_magnitude(&values.ray_dir);
		vec_normalize(&ray_dir);
		is_on_view(game, &game->ghost, ray_dir);
		is_on_view(game, &game->final, ray_dir);
		ft_memset(game->buffer, 0, SCREENHEIGHT);
		render_engine(&values, game);
		game->z_buffer[values.rays] = values.perp_wall;
		values.rays++;
	}
}
