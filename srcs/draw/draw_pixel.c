#include <cub3d.h>

void	draw_pixel(t_data *data, t_vec point, int color)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length \
	+ ((int)point.x) * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_data *data, t_vec point)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length \
	+ ((int)point.x) * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	clean_map(t_game *game)
{
	int	col;
	int	line;
	int	c;

	col = 0;
	line = 0;
	while (line < SCREENHEIGHT)
	{
		col = 0;
		while (col < SCREENWIDTH)
		{
			if (line < SCREENHEIGHT / 2)
				draw_pixel(&game->resources.canvas, (t_vec){.x = col, \
				.y = line}, game->resources.ceil_color);
			else
				draw_pixel(&game->resources.canvas, (t_vec){.x = col, \
				.y = line}, game->resources.floor_color);
			col++;
		}
		line++;
	}
}
