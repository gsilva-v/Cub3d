#include <cub3d.h>

static void	clean_map(t_game *game)
{
	int	col;
	int	line;

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

int	game_render(t_game *game)
{
	// static float second;
	// static int	frame;

	game->elapsed_time = passed_time(game->last_time);
	// second += game->elapsed_time;
	game->last_time = current_time();
	// frame++;
	// if (second >= 1)
	// {
	// 	char *buffer;
	// 	buffer =  ft_itoa(frame);
	// 	write (1, buffer, ft_strlen(buffer));
	// 	write(1, "\n", 1);
	// 	frame = 0;
	// 	second = 0;
	// }
	if (game->is_on_focus)
		mlx_mouse_move(game->mlx, game->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	clean_map(game);
	game_update(game);
	player_render(game);
	mlx_put_image_to_window(game->mlx, game->win, \
	game->resources.canvas.img, 0, 0);
	return (0);
}
