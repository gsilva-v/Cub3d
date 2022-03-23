#include <cub3d.h>

int	check_horizontal_wall(char **map, int x, int y)
{
	int	tmp_x;

	tmp_x = x;
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
	return (1);
}

int	check_vertical_wall(char **map, int x, int y)
{
	int	tmp_y;

	tmp_y = y;
	while (map[y] && map[y][x] != WALL)
		y++;
	if (map[y] == 0 || map[y][x] != WALL)
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

int	check_surrounded(char **map, int x, int y)
{
	int	tmp_x;

	tmp_x = x;
	if (!check_horizontal_wall(map, x, y))
		return (0);
	x = tmp_x;
	if (!check_vertical_wall(map, x, y))
		return (0);
	return (1);
}
