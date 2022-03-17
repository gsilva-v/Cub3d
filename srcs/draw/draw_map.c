#include <cub3d.h>

void	clean_map(t_game *game)
{
	int col = 0, line;

	while (col < 16 * 64)
	{
		line = 0;
		while(line < 8 * 64)
		{
			drawpixel(&game->canvas, (t_vec){.x = col, .y = line }, 0);
			line++;
		}
		col++;
	}
}

void	draw_map(t_game *game)
{
	int col = 0, line;

	while (col < 8)
	{
		line = 0;
		while(line < 8)
		{
			if (game->map[line][col] == 1)
				draw_square(&game->canvas, (t_vec){.x = col * 64, .y = line * 64}, 64 - 1, 0xFFFFFF);
			else if (game->map[line][col] == 0)
				draw_square(&game->canvas, (t_vec){.x = col * 64, .y = line * 64}, 64 - 1, 0);
			line++;
		}
		col++;
	}
}
