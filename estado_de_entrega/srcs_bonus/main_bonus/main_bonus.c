/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:28:12 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:28:13 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\n%s\n", WRONG_ARG);
		exit(1);
	}
	ft_bzero(&game, sizeof(game));
	game.player.pos.x = -1.0f;
	game.player.pos.y = -1.0f;
	if (parse_resources(&game, argv[1]))
		return (1);
	if (parse_map(&game, argv[1]))
		return (1);
	init_game(&game);
	load_imgs(&game);
	game_run(&game);
	return (0);
}
