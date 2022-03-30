#include <cub3d_bonus.h>

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
	game_update(game);
	game->elapsed_time = passed_time(game->last_time);
	game->last_time = current_time();
	if (game->is_on_focus && !game->lose)
		mlx_mouse_move(game->mlx, game->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	clean_map(game);
	player_render(game);
	sprite_render(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, \
	game->resources.canvas.img, 0, 0);
	if (game->lose)
		mlx_string_put(game->mlx, game->win, 150, 150, 0xff0000, " You lose, try again! ");
	return (0);
}
