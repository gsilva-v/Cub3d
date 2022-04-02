/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_window_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:27:02 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:27:05 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	red_cross(t_game *game)
{
	finish_him(game, 0);
	return (1);
}

void	kill_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_loop_end(game->mlx);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
