#include <cub3d.h>

void	player_north(t_game *game, int x, int y)
{
	game->player = (t_player){
		.direction = {.y = -1, .x = 0},
		.plane = {.y = 0, .x = 0.66},
		.pos = {.y = y, .x = x}
	};
	game->map[y][x] = FLOOR;
}

void	player_south(t_game *game, int x, int y)
{
	game->player = (t_player){
		.direction = {.y = 1, .x = 0},
		.plane = {.y = 0, .x = -0.66},
		.pos = {.y = y, .x = x}
	};
	game->map[y][x] = FLOOR;
}

void	player_west(t_game *game, int x, int y)
{
	game->player = (t_player){
		.direction = {.y = 0, .x = -1},
		.plane = {.y = -0.66, .x = 0},
		.pos = {.y = y, .x = x}
	};
	game->map[y][x] = FLOOR;
}

void	player_east(t_game *game, int x, int y)
{
	game->player.direction = (t_vec){.y = 0, .x = 1};
	game->player.plane = (t_vec){.y = 0.66, .x = 0};
	game->player.pos = (t_vec){.y = y, .x = x};
	game->map[y][x] = FLOOR;
}
