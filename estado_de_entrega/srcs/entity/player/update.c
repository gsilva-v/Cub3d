/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:25:43 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:25:44 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	player_update(t_game *game)
{
	static float	movespeed;

	if (!movespeed)
		movespeed = game->player.movespeed;
	if (game->buttons.acelerate)
		game->player.movespeed *= 1.2;
	else
		game->player.movespeed *= 0.8;
	if (game->player.movespeed > 2 * movespeed)
		game->player.movespeed = 2 * movespeed;
	else if (game->player.movespeed < movespeed)
		game->player.movespeed = movespeed;
	watch_rotate(game);
	watch_walk(game);
	watch_strafe(game);
	watch_functions(game);
}
