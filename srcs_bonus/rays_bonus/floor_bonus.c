#include <cub3d_bonus.h>

static void	reset_values(t_floor *floor, int y, t_game *game)
{
	int		pos;
	float	pos_z;

	floor->raydir0 = game->player.direction;
	vec_sub(&floor->raydir0, &game->player.plane);
	floor->raydir1 = game->player.direction;
	vec_sum(&floor->raydir1, &game->player.plane);
//  pega o ponto x = 0, y = screenheight/2 e transforma em x = 0, y = 0
	pos = y - SCREENHEIGHT / 2;
//  calculo da perspectiva do chao
	// calculo da profundidade
	pos_z = 0.5 * SCREENHEIGHT;
	// calculo da distancia do chao
	floor->rowDistance = pos_z / pos;
	// setar o quanto vai diminuir dependendo da distancia
	floor->step.x = floor->rowDistance * (floor->raydir1.x - \
	floor->raydir0.x) / SCREENWIDTH;
	floor->step.y = floor->rowDistance * (floor->raydir1.y - \
	floor->raydir0.y) / SCREENWIDTH;
	// setar onde vai começar ser printado
	floor->pos.x = game->player.pos.x + floor->rowDistance * \
	floor->raydir0.x;
	floor->pos.y = game->player.pos.y + floor->rowDistance * \
	floor->raydir0.y;
}

static void	pick_texture(t_floor *floor)
{
	t_int_vec	cell;

	cell.x = (int)(floor->pos.x);
	cell.y = (int)(floor->pos.y);
	// get the texture coordinate from the fractional part
	floor->text.x = (int)(BLOCK_SIZE * (floor->pos.x - cell.x));
	floor->text.y = (int)(BLOCK_SIZE * (floor->pos.y - cell.y));
	floor->pos.x += floor->step.x;
	floor->pos.y += floor->step.y;
}

void	floor_casting(t_game *game)
{
	t_floor floor;
	int y;
	int x;
 	int	color;

	y = SCREENHEIGHT / 2;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		reset_values(&floor, y, game);
		while (x < SCREENWIDTH)
		{
			pick_texture(&floor);
			color = get_pixel(&game->resources.floor, \
			(t_vec){.x = floor.text.x, .y = floor.text.y});
			color = lamp((t_vec){.x = x, .y = y}, game, color, \
			floor.rowDistance);
			color = reshade(color);
			draw_pixel(&game->resources.canvas, (t_vec){.x = x, \
			.y =y}, color);
			x++;
		}
		y++;
	}
}
