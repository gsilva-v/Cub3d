/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:25:51 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 17:13:32 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N')
				player_north(game, x, y);
			if (game->map[y][x] == 'S')
				player_south(game, x, y);
			if (game->map[y][x] == 'W')
				player_west(game, x, y);
			if (game->map[y][x] == 'E')
				player_east(game, x, y);
			x++;
		}
		y++;
	}
	if (game->player.pos.x == -1.0f || game->player.pos.y == -1.0f)
		show_error(game, 1, WTOUT_PLYR);
	game->player.pos.x += 0.5f;
	game->player.pos.y += 0.5f;
}

void	init_game(t_game *game)
{
	init_player(game);
	game->player.movespeed = 0.1f;
	game->buffer = ft_calloc(1, SCREENHEIGHT);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREENWIDTH, SCREENHEIGHT, "RAY");
}
