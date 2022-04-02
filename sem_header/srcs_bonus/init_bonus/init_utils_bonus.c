#include <cub3d_bonus.h>

int	get_number_ghost(t_game *game)
{
	int	index;
	int	y;
	int	x;

	index = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'G')
				index++;
			x++;
		}
		y++;
	}
	return (index);
}

int	player_on_view(char **map, int x, int y)
{
	int	width;
	int	height;
	int	y_tmp;

	y_tmp = y;
	width = x + 10;
	height = y + 10;
	while (x < width)
	{
		y = y_tmp;
		while (y < height)
		{
			if (x < get_higher_len(map) && y < matrix_len(map))
			{
				if (ft_char_in_set(map[y][x], "NSWE"))
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

void	move_minimap_cam(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < matrix_len(game->map))
	{
		x = 0;
		while (x < get_higher_len(game->map))
		{
			if (player_on_view(game->map, x, y))
			{
				game->map_offset.x = x * 10;
				game->map_offset.y = y * 10;
				return ;
			}
			x++;
		}
		y++;
	}
}
