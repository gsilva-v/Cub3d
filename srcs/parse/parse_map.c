#include <cub3d.h>

int	is_surrounded(t_game *game)
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

int	advance_to_map(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] != 'C')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	else
		return (1);
	return (0);
}

char	**get_map(int fd, char *line)
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
		show_error(game, 1, "cannot open file map");
	if (advance_to_map(fd))
		close_exit(fd, INV_CFG);
	line = get_next_line(fd);
	if (ft_strncmp(line, "\n", -1))
	{
		free(line);
		show_error(game, 1, INV_CFG);
	}
	if (!line)
		close_exit(fd, "This file don't have a map!");
	game->map = get_map(fd, line);
	if (!game->map)
		close_exit(fd, "This map have invalid caracters!");
	close (fd);
	if (!is_surrounded(game))
		show_error(game, 1, "This map have a hole for space");
	return (0);
}
