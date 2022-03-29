#include <cub3d_bonus.h>

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
	if (game->player.pos.x == -1.0f || game->player.pos.y == -1.0f)
		show_error(game, 1, WTOUT_PLYR);
	game->player.pos.x += 0.5f;
	game->player.pos.y += 0.5f;
}

int		init_sprites(t_game *game)
{
	while(1)
	{
		game->sprite_pos.x = (float)rand()/(float)(RAND_MAX/ get_higher_len(game->map) - 1);
		game->sprite_pos.y = (float)rand()/(float)(RAND_MAX/ matrix_len(game->map) - 1);
		if (game->map[(int)game->sprite_pos.y][(int)game->sprite_pos.x] == FLOOR)
			break;
	}
}
void	init_game(t_game *game)
{
	srand(time(NULL));
	game->mlx = mlx_init();
	init_player(game);
	init_sprites(game);
	game->player.movespeed = 3.0f;
	game->buffer = ft_calloc(1, SCREENHEIGHT);
	game->z_buffer = ft_calloc(sizeof(float), SCREENWIDTH);
	game->win = mlx_new_window(game->mlx, SCREENWIDTH, SCREENHEIGHT, "RAY");
}
