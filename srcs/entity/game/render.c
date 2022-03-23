#include <cub3d.h>

int	game_render(t_game *game)
{
	clean_map(game);
	game_update(game);
	player_render(game);
	int	color;
	int	y;
	int	x;

	y = 0;
	while (y < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			color = get_pixel(&game->resources.pov, (t_vec){.x = x, .y = y});
			if (color != 4079166)
				draw_pixel(&game->resources.canvas, (t_vec){.x =x, .y=y}, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->resources.canvas.img, 0, 0);
}