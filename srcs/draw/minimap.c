#include <cub3d.h>

void	draw_square(t_data *canvas, t_vec point, int size, int color)
{
	int	x;
	int	y;

	x = point.x;
	while (x < point.x + size)
	{
		y = point.y;
		while (y < point.y + size)
		{
			draw_pixel(canvas, (t_vec){.x = x, .y = y}, color);
			y++;
		}
		x++;
	}
}

void	draw_map(t_game *game)
{
	int col;
	int line;

	col = 0;
	line = 0;

	while (game->map[line])
	{
		col = 0;
		while(game->map[line][col])
		{
		
			if (game->map[line][col] == WALL)
				draw_square(&game->resources.canvas, (t_vec){.x = col * 10, .y = line * 10}, 10 - 1, 0xFFFFFF);
			else if (game->map[line][col] == DOOR)
				draw_square(&game->resources.canvas, (t_vec){.x = col * 10, .y = line * 10}, 10 - 1, 0xFF00FF);
			else if (game->map[line][col] == FLOOR)
				draw_square(&game->resources.canvas, (t_vec){.x = col * 10, .y = line * 10}, 10 - 1, 0);
			else if (game->map[line][col] == OPEN_DOOR)
				draw_square(&game->resources.canvas, (t_vec){.x = col * 10, .y = line * 10}, 10 - 1, 0x00ff00);
			col++;
		}
		line++;
	}
	draw_square(&game->resources.canvas, (t_vec){.x = game->player.pos.x * 10, .y = game->player.pos.y * 10}, 5, 0x0000ff);
	
}


void	minimap(t_game *game)
{

	draw_map(game);
}