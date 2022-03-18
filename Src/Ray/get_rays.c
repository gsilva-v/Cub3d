#include <ray.h>

t_vec	get_horizontal_ray(float ray_angle, t_game *game)
{
	t_vec	ray;
	t_vec	offset;
	t_ivec	map_pos;
	t_vec	hori_pos;
	int		doff = 0;

	// HORIZONTAL CHECK
	hori_pos.x = game->player.position.x;
	hori_pos.y = game->player.position.y;
	hori_pos.magnitude = 100000;
	doff = 0;
	float	aTan = -1 / tan(ray_angle);
	if (ray_angle > PI) //looking down
	{
		ray.y = (((int)game->player.position.y >> 6) << 6) - 0.0001f; // multiplo de 64  mais proximo pra baixo
		ray.x = (game->player.position.y - ray.y) * aTan + game->player.position.x;
		offset.y = -64; //proxima posiçao do y
		offset.x = -offset.y * aTan; //proxima posição do x
	}
	if (ray_angle < PI) //looking up
	{
		ray.y = (((int)game->player.position.y >> 6) << 6) + 64; // multiplo de 64  mais proximo pra baixo
		ray.x = (game->player.position.y - ray.y) * aTan + game->player.position.x;
		offset.y = 64; //proxima posiçao do y
		offset.x = -offset.y * aTan; //proxima posição do x
	}
	if (ray_angle == 0 || ray_angle == PI)
	{
		ray.x = game->player.position.x;
		ray.y = game->player.position.y;
		doff = HEIGHT;
	}
	while (doff < HEIGHT)
	{
		map_pos.x = (int) (ray.x) >> 6;
		map_pos.y = (int) (ray.y) >> 6;
		if (ray.x < WIDTH * 64 && ray.y < HEIGHT * 64 && ray.x > 9 && ray.y > 9)
			draw_circle(ray, 5, &game->server.canvas, 0x0000FF);
		if ((map_pos.x < WIDTH && map_pos.y < HEIGHT && map_pos.x >= 0 && map_pos.y >= 0) && game->map[map_pos.y][map_pos.x] > 0)
		{
			hori_pos.magnitude = get_dist(game->player.position, (t_vec){.x=ray.x, .y=ray.y});
			hori_pos.x = ray.x;
			hori_pos.y = ray.y;
			doff = HEIGHT;
		}
		else
		{
			ray.x += offset.x;
			ray.y += offset.y;
			doff++;
		}
	}
	return (hori_pos);
}

t_vec	get_vertical_ray(float ray_angle, t_game *game)
{
	t_vec	ray;
	t_vec	offset;
	t_ivec	map_pos;
	t_vec	vert_pos;
	int		doff = 0;

	vert_pos.x = game->player.position.x;
	vert_pos.y = game->player.position.y;
	vert_pos.magnitude = 100000;
	float	nTan = -tan(ray_angle);
	if (ray_angle > P2 && ray_angle < P3) //looking left
	{
		ray.x = (((int)game->player.position.x >> 6) << 6) - 0.0001f; // multiplo de 64  mais proximo pra baixo
		ray.y = (game->player.position.x - ray.x) * nTan + game->player.position.y;
		offset.x = -64; //proxima posiçao do y
		offset.y = -offset.x * nTan; //proxima posição do x
	}
	if (ray_angle < P2 || ray_angle > P3) //looking right
	{
		ray.x = (((int)game->player.position.x >> 6) << 6) + 64; // multiplo de 64  mais proximo pra baixo
		ray.y = (game->player.position.x - ray.x) * nTan + game->player.position.y;
		offset.x = 64; //proxima posiçao do y
		offset.y = -offset.x * nTan; //proxima posição do x
	}
	if (ray_angle == 0 || ray_angle == PI)//looking up or down
	{
		ray.x = game->player.position.x;
		ray.y = game->player.position.y;
		doff = WIDTH;
	}
	while (doff < WIDTH)
	{
		map_pos.x = (int) (ray.x) >> 6;
		map_pos.y = (int) (ray.y) >> 6;
		if (ray.x < WIDTH * 64 && ray.y < HEIGHT * 64 && ray.x > 9 && ray.y > 9)
			draw_circle(ray, 5, &game->server.canvas, 0xFF0000);
		if ((map_pos.x < WIDTH && map_pos.y < WIDTH && map_pos.x >= 0 && map_pos.y >= 0) && game->map[map_pos.y][map_pos.x] > 0)
		{
			vert_pos.magnitude = get_dist(game->player.position, (t_vec){.x=ray.x, .y=ray.y});
			vert_pos.x = ray.x;
			vert_pos.y = ray.y;
			doff = WIDTH;
		}
		else
		{
			ray.x += offset.x;
			ray.y += offset.y;
			doff++;
		}
	}
	return (vert_pos);
}

/*
	@brief	Set ray to the closest ray of ray_angle direction
	@returns Return 1 when ray is horizontal and 2 when ray is vertical
*/
int	get_ray(t_vec *ray, float ray_angle, t_game *game)
{
	t_vec	horizontal;
	t_vec	vertical;

	horizontal = get_horizontal_ray(ray_angle, game);
	vertical = get_vertical_ray(ray_angle, game);
	if (horizontal.magnitude < vertical.magnitude)
	{
		ray->x = horizontal.x;
		ray->y = horizontal.y;
		ray->magnitude = horizontal.magnitude;
		ray->first_pixel = (int)ray->x - (((int)ray->x >> 6) << 6);
		ray->direction = HORIZONTAL;
		return (HORIZONTAL);
	}
	else if (vertical.magnitude < horizontal.magnitude)
	{
		ray->x = vertical.x;
		ray->y = vertical.y;
		ray->magnitude = vertical.magnitude;
		ray->first_pixel = (int)ray->y - (((int)ray->y >> 6) << 6);
		ray->direction = VERTICAL;
		return (VERTICAL);
	}
	return (0);
}
