#include <cub3d.h>

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
	int hit = 0;
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

void	raycasting(t_game *game)
{
	t_rays	values;

	values.rays = 0;

	/* for (int y = 0; y < SCREENHEIGHT; y++)
	{
		//Direction menos plane
		t_vec	rayDir0 = game->player.direction;
		vec_sub(&rayDir0, &game->player.plane);
		//Direction mais plane
		t_vec	rayDir1 = game->player.direction;
		vec_sum(&rayDir1, &game->player.plane);

		//ponto atual do y comparado com o meio da tela
		int point = y - SCREENHEIGHT / 2;

		//posiçaõ vertical da camera
		float	posZ = 0.5 * SCREENHEIGHT;

		float	rowDistance = posZ / point;


		t_vec	floorStep = {
			.x = (rowDistance * (rayDir1.x - rayDir0.x) / SCREENWIDTH),
			.y = (rowDistance * (rayDir1.y - rayDir0.y) / SCREENWIDTH)
		};

		t_vec	floor = {
			.x = (game->player.pos.x + rowDistance * rayDir0.x),
			.y = (game->player.pos.y + rowDistance * rayDir0.y)
		};
		for (int x = 0; x < SCREENWIDTH; x++)
		{
			t_int_vec	cell = {
				.x = (int)floor.x,
				.y = (int)floor.y
			};
			vec_sum(&floor, &floorStep);

			t_int_vec	texture_position = {
				.x = (int) (BLOCK_SIZE * (floor.x - cell.x)) & (BLOCK_SIZE - 1),
				.y = (int) (BLOCK_SIZE * (floor.y - cell.y)) & (BLOCK_SIZE - 1)
			}

		}
	} */
	while (values.rays < SCREENWIDTH)
	{
		// reset values
		reset_values(&values, &game->player);
		// calculo de distancias atuais
		check_dist(&values, &game->player);
		// algoritmo DDA
		dda(&values, game);
		// renderização
		ft_memset(game->buffer, 0, SCREENHEIGHT);
		render_engine(&values, game);
		values.rays++;
	}
}
