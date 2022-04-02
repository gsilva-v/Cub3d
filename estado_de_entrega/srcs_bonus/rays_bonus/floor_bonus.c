/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:28:34 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:32:27 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	reset_values(t_floor *floor, int y, t_game *game)
{
	int		pos;
	float	pos_z;

	floor->raydir0 = game->player.direction;
	vec_sub(&floor->raydir0, &game->player.plane);
	floor->raydir1 = game->player.direction;
	vec_sum(&floor->raydir1, &game->player.plane);
	pos = y - SCREENHEIGHT / 2;
	pos_z = 0.5 * SCREENHEIGHT;
	floor->row_dist = pos_z / pos;
	floor->step.x = floor->row_dist * (floor->raydir1.x - \
	floor->raydir0.x) / SCREENWIDTH;
	floor->step.y = floor->row_dist * (floor->raydir1.y - \
	floor->raydir0.y) / SCREENWIDTH;
	floor->pos.x = game->player.pos.x + floor->row_dist * \
	floor->raydir0.x;
	floor->pos.y = game->player.pos.y + floor->row_dist * \
	floor->raydir0.y;
}

static void	pick_texture(t_floor *floor)
{
	t_int_vec	cell;

	cell.x = (int)(floor->pos.x);
	cell.y = (int)(floor->pos.y);
	floor->text.x = (int)(BLOCK_SIZE * (floor->pos.x - \
	cell.x)) & (BLOCK_SIZE - 1);
	floor->text.y = (int)(BLOCK_SIZE * (floor->pos.y - \
	cell.y)) & (BLOCK_SIZE - 1);
	floor->pos.x += floor->step.x;
	floor->pos.y += floor->step.y;
}

void	floor_casting(t_game *game)
{
	t_floor		floor;
	t_int_vec	pos;
	t_vec		aux;
	int			color;

	pos.y = SCREENHEIGHT / 2;
	while (pos.y < SCREENHEIGHT)
	{
		pos.x = 0;
		reset_values(&floor, pos.y, game);
		while (pos.x < SCREENWIDTH)
		{
			pick_texture(&floor);
			color = get_pixel(&game->resources.floor, \
			(t_vec){.x = floor.text.x, .y = floor.text.y});
			aux = (t_vec){.x = pos.x, .y = pos.y};
			color = lamp(aux, game, color, \
			floor.row_dist);
			color = reshade(color);
			draw_pixel(&game->resources.canvas, aux, color);
			pos.x++;
		}
		pos.y++;
	}
}
