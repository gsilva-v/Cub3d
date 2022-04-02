/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:26:04 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:26:05 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_horizontal_wall(char **map, int x, int y)
{
	int	tmp_x;

	tmp_x = x;
	while (map[y][x] && map[y][x] != WALL && map[y][x] != ' ')
		x++;
	if (map[y][x] != WALL || map[y][x] == ' ')
		return (0);
	x = tmp_x;
	while (x >= 0 && map[y][x] != WALL && map[y][x] != ' ')
		x--;
	if (x < 0)
		x = 0;
	if (map[y][x] != WALL || map[y][x] == ' ')
		return (0);
	return (1);
}

int	check_vertical_wall(char **map, int x, int y)
{
	int	tmp_y;

	tmp_y = y;
	while (map[y] && map[y][x] != WALL && map[y][x] != ' ')
		y++;
	if (map[y] == 0 || map[y][x] != WALL || map[y][x] == ' ')
		return (0);
	y = tmp_y;
	while (y >= 0 && map[y][x] != WALL && map[y][x] != ' ')
		y--;
	if (y < 0)
		y = 0;
	if (map[y][x] != WALL || map[y][x] == ' ')
		return (0);
	return (1);
}
