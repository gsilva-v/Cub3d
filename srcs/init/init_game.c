#include <cub3d.h>

void	init_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N')
				player_north(game, x, y);
			if (game->map[y][x] == 'S')
				player_south(game, x, y);
			if (game->map[y][x] == 'W')
				player_west(game, x, y);
			if (game->map[y][x] == 'E')
				player_east(game, x, y);
			x++;
		}
		y++;
	}
	game->player.pos.x += 0.5f;
	game->player.pos.y += 0.5f;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	init_player(game);
	game->player.movespeed = 0.1f;
	game->win = mlx_new_window(game->mlx, SCREENWIDTH, SCREENHEIGHT, "RAY");
}
