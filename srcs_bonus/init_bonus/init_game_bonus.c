#include <cub3d_bonus.h>

static void	init_player(t_game *game)
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

static void	init_sprites(t_game *game)
{
	float	dist;

	while (1)
	{
		game->ghost.pos.x = (float)rand()
			/ (float)(RAND_MAX / get_higher_len(game->map) - 1);
		game->ghost.pos.y = (float)rand()
			/ (float)(RAND_MAX / matrix_len(game->map) - 1);
		dist = vec_dist(game->ghost.pos, game->player.pos);
		if (game->map[(int)game->ghost.pos.y]
			[(int)game->ghost.pos.x] == FLOOR && dist >= 3)
			break ;
	}
}

static void	init_final_point(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->final.pos.x = -1;
	game->final.pos.y = -1;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'F' && game->final.pos.x == -1)
			{
				game->final.pos.x = x + 0.5f;
				game->final.pos.y = y + 0.5f;
				game->map[y][x] = FLOOR;
			}
			else if (game->map[y][x] == 'F' && game->final.pos.x != -1)
				show_error(game, 1, "This map have 2 or more finals!");
			x++;
		}
		y++;
	}
	if (game->final.pos.x == -1)
		show_error(game, 1, "This map dont have a final!");
}

void	init_game(t_game *game)
{
	srand(time(NULL));
	game->mlx = mlx_init();
	init_player(game);
	init_sprites(game);
	init_final_point(game);
	game->player.movespeed = 3.0f;
	game->buffer = ft_calloc(1, SCREENHEIGHT);
	game->z_buffer = ft_calloc(sizeof(float), SCREENWIDTH);
	game->win = mlx_new_window(game->mlx, SCREENWIDTH, SCREENHEIGHT, "RAY");
}
