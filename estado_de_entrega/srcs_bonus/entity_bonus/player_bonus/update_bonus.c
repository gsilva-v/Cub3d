/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:27:41 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:27:42 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	player_update(t_game *game)
{
	if (game->lose)
		return ;
	watch_rotate(game);
	watch_walk(game);
	watch_strafe(game);
	watch_functions(game);
}
