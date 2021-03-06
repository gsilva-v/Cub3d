/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:27:24 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:27:25 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	enter_window(t_game *game)
{
	game->is_on_focus = 1;
	return (0);
}

int	leave_window(t_game *game)
{
	game->is_on_focus = 0;
	return (0);
}

int	rotate(int x, int y, t_game *game)
{
	int			move;
	t_int_vec	middle_screen;

	(void)y;
	middle_screen = (t_int_vec){
		.x = SCREENWIDTH / 2,
		.y = SCREENHEIGHT / 2
	};
	move = x - middle_screen.x;
	if (x != middle_screen.x)
		game->player.rotate_cam = move * 0.08f;
	return (0);
}
