#include <cub3d.h>

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

			/* c = get_pixel(&game->resources.pov, (t_vec){.x = col, .y = line});
			if (c != 0xff00ff)
				draw_pixel(&game->resources.canvas, \
				(t_vec){.x = col, .y = line}, c);
			else  */



/* void	draw_map(t_game *game)
{
	int col = 0, line;

	while (col < 8)
	{
		line = 0;
		while(line < 8)
		{
			if (game->map[line][col] == 1)
				draw_square(&game->canvas, (t_vec){.x = col * BLOCK_SIZE, .y = line * BLOCK_SIZE}, BLOCK_SIZE - 1, 0xFFFFFF);
			else if (game->map[line][col] == 2)
				draw_square(&game->canvas, (t_vec){.x = col * BLOCK_SIZE, .y = line * BLOCK_SIZE}, BLOCK_SIZE - 1, 0xFF00FF);
			else if (game->map[line][col] == 0)
				draw_square(&game->canvas, (t_vec){.x = col * BLOCK_SIZE, .y = line * BLOCK_SIZE}, BLOCK_SIZE - 1, 0);
			line++;
		}
		col++;
	}
}
 */