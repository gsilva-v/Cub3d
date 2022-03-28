#include <cub3d_bonus.h>

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
				draw_square(&game->resources.map, (t_vec){.x = col * MAP_BLOCK_SIZE, .y = line * MAP_BLOCK_SIZE}, MAP_BLOCK_SIZE - 1, 0xFFFFFF);
			else if (game->map[line][col] == DOOR)
				draw_square(&game->resources.map, (t_vec){.x = col * MAP_BLOCK_SIZE, .y = line * MAP_BLOCK_SIZE}, MAP_BLOCK_SIZE - 1, 0xFF00FF);
			else if (game->map[line][col] == FLOOR)
				draw_square(&game->resources.map, (t_vec){.x = col * MAP_BLOCK_SIZE, .y = line * MAP_BLOCK_SIZE}, MAP_BLOCK_SIZE - 1, 0);
			else if (game->map[line][col] == OPEN_DOOR)
				draw_square(&game->resources.map, (t_vec){.x = col * MAP_BLOCK_SIZE, .y = line * MAP_BLOCK_SIZE}, MAP_BLOCK_SIZE - 1, 0x00ff00);
			col++;
		}
		line++;
	}
}


void	minimap(t_game *game)
{
	int col;
	int line;
	int	y;
	int	x;

	y = 0;
	line = game->map_offset.y;
	while (line < game->map_offset.y + 100)
	{
		x = 0;
		col = game->map_offset.x;
		while(col < game->map_offset.x + 100)
		{
			int	color = get_pixel(&game->resources.map, (t_vec){.x = col, .y = line});
			draw_pixel(&game->resources.canvas, (t_vec){.x = x, .y = y}, color);
			col++;
			x++;
		}
		y++;
		line++;
	}
	draw_square(&game->resources.canvas, (t_vec){.x = game->player.pos.x * 10 - game->map_offset.x, .y = game->player.pos.y * 10 - game->map_offset.y}, 5, 0x0000ff);
}