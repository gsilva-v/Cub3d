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
			{
				game->player = (t_player){
					.direction = {.y = -1, .x = 0},
					.plane = {.y = 0, .x = 0.66},
					.pos = {.y = y, .x = x}
				};
				game->map[y][x] = FLOOR;
			}
			if (game->map[y][x] == 'S')
			{
				game->player = (t_player){
					.direction = {.y = 1, .x = 0},
					.plane = {.y = 0, .x = -0.66},
					.pos = {.y = y, .x = x}
				};
				game->map[y][x] = FLOOR;
			}
			if (game->map[y][x] == 'W')
			{
				game->player = (t_player){
					.direction = {.y = 0, .x = -1},
					.plane = {.y = -0.66, .x = 0},
					.pos = {.y = y, .x = x}
				};
				game->map[y][x] = FLOOR;
			}
			if (game->map[y][x] == 'E')
			{

				game->player.direction = (t_vec){.y = 0, .x = 1};
				game->player.plane = (t_vec){.y = 0.66, .x = 0};
				game->player.pos = (t_vec){.y = y, .x = x};
				game->map[y][x] = FLOOR;
			}
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
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "RAY");
}