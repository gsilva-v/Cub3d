#include <cub3d.h>


int	valid_direction(t_game *game, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (game->walk[y] == 0 || game->walk[y][x] == -1)
		return (0);
	if (game->map[y][x] != WALL)
		return (0);
	return (1);
}

int	check_surrounded(char **map, int x, int y)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = x;
	tmp_y = y;
	while (map[y][x] && map[y][x] != WALL)
		x++;
	if (map[y][x] != WALL)
		return (0);
	x = tmp_x;
	while (x >= 0 && map[y][x] != WALL)
		x--;
	if (x < 0)
		x = 0;
	if (map[y][x] != WALL)
		return (0);
	x = tmp_x;
	while (map[y] && map[y][x] != WALL)
		y++;
	if (map[y][x] != WALL)
		return (0);
	y = tmp_y;
	while (y >= 0 && map[y][x] != WALL)
		y--;
	if (y < 0)
		y = 0;
	if (map[y][x] != WALL)
		return (0);
	return (1);
}

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

int	parse_map(t_game *game, char *file)
{
	int fd;
	char *line;
	char *map_str;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
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
	line = get_next_line(fd);
	if (!line)
		return (1);
	map_str = ft_strdup("");
	int i = 0;
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_char_in_set(line[i], VALID_BLOCK))
				return (1);
			i++;
		}	
		map_str = ft_strjoin(map_str, line);
		free(line);
		line = get_next_line(fd);
	}
	game->map = ft_split(map_str, '\n');
	if (!is_surrounded(game))
		return (1);
	close(fd);
	free(map_str);
	return (0);
}