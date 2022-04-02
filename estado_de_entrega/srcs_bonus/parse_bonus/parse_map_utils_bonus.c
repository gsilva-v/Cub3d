/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:28:19 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 17:24:11 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static char	*normalize_line(char *line, int size)
{
	int		index;
	char	*new_line;

	new_line = ft_calloc(size + 1, sizeof(char));
	ft_memset(new_line, WALL, size);
	index = 0;
	while (line[index])
	{
		new_line[index] = line[index];
		index++;
	}
	free(line);
	return (new_line);
}

void	normalize_map(t_game *game)
{
	int	index;
	int	size;

	size = get_higher_len(game->map);
	index = 0;
	while (game->map[index])
	{
		if (ft_strlen(game->map[index]) < size)
			game->map[index] = normalize_line(game->map[index], size);
		index++;
	}
}

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
	while (map[y] && map[y][x] && map[y][x] != WALL && map[y][x] != ' ')
		y++;
	if (map[y] == 0 || map[y][x] != WALL || map[y][x] == ' ')
		return (0);
	y = tmp_y;
	while (y >= 0 && map[y][x] && map[y][x] != WALL && map[y][x] != ' ')
		y--;
	if (y < 0)
		y = 0;
	if (map[y][x] != WALL || map[y][x] == ' ')
		return (0);
	return (1);
}
