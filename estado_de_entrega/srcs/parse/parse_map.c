/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:26:07 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/04 09:09:16 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_surrounded(char **map, int x, int y)
{
	if (!check_horizontal_wall(map, x, y))
		return (0);
	if (!check_vertical_wall(map, x, y))
		return (0);
	if (!check_diagonalup_wall(map, x, y))
		return (0);
	if (!check_diagonaldown_wall(map, x, y))
		return (0);
	return (1);
}

static int	is_surrounded(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_char_in_set(game->map[y][x], "ESWN02"))
			{
				if (!check_surrounded(game->map, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static char	*advance_to_map(int fd)
{
	char	*tmp;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, " ");
		if (tmp[0] == '1')
		{
			free(tmp);
			break ;
		}
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static char	**get_map(int fd, char *line)
{
	int		i;
	char	*map_str;
	char	**map_arr;

	map_str = ft_strdup("");
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_char_in_set(line[i], VALID_BLOCK))
			{
				free (line);
				free (map_str);
				return (NULL);
			}
			i++;
		}	
		map_str = ft_strjoin(map_str, line);
		free(line);
		line = get_next_line(fd);
	}
	map_arr = ft_split(map_str, '\n');
	free(map_str);
	return (map_arr);
}

int	parse_map(t_game *game, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		show_error(game, 1, "Cannot open file map");
	line = advance_to_map(fd);
	if (!line)
	{
		close(fd);
		show_error(game, 1, INV_CFG);
	}
	game->map = get_map(fd, line);
	if (!game->map)
	{
		close(fd);
		show_error(game, 1, "This map have invalid caracters!");
	}
	close (fd);
	if (!is_surrounded(game))
		show_error(game, 1, "This map have a hole for space");
	return (0);
}
