#include <cub3d.h>

void	set_colisions(t_game *game)
{
	game->colisions.offset.x = 20;
	if (game->direction.x < 0)
		game->colisions.offset.x = -20;
	game->colisions.offset.y = 20;
	if (game->direction.y < 0)
		game->colisions.offset.y = -20;
	game->colisions.ip.x = game->player.x / 64;
	game->colisions.ip_add_offset.x = (game->player.x + \
	game->colisions.offset.x) / 64;
	game->colisions.ip_sub_offset.x = (game->player.x - \
	game->colisions.offset.x) / 64;
	game->colisions.ip.y = game->player.y / 64;
	game->colisions.ip_add_offset.y = (game->player.y + \
	game->colisions.offset.y) / 64;
	game->colisions.ip_sub_offset.y = (game->player.y - \
	game->colisions.offset.y) / 64;
}

void	move_forward(t_game *game)
{
	if (game->map[game->colisions.ip.y][game->colisions.ip_add_offset.x] == 0)
		game->player.x += game->direction.x;
	if (game->map[game->colisions.ip_add_offset.y][game->colisions.ip.x] == 0)
		game->player.y += game->direction.y;
}

void	move_back(t_game *game)
{
	if (game->map[game->colisions.ip.y][game->colisions.ip_sub_offset.x] == 0)
		game->player.x -= game->direction.x;
	if (game->map[game->colisions.ip_sub_offset.y][game->colisions.ip.x] == 0)
		game->player.y -= game->direction.y;
}

void	look_right(t_game *game)
{
	game->player_angle += 0.1f;
	if (game->player_angle > 2 * PI)
		game->player_angle -= 2 * PI; 
	game->direction.x = cos(game->player_angle) * 5;
	game->direction.y = sin(game->player_angle) * 5;
}

void	look_left(t_game *game)
{
	game->player_angle -= 0.1f;
	if (game->player_angle < 0)
		game->player_angle += 2 * PI; 
	game->direction.x = cos(game->player_angle) * 5;
	game->direction.y = sin(game->player_angle) * 5;
}
