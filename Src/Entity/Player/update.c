#include <ray.h>

int	player_update(int keycode, t_game *game)
{
	t_vec	offset;

	offset.x = 0;
	if (game->player.delta_x < 0)
		offset.x = -20;
	else
		offset.x = 20;
	offset.y = 0;
	if (game->player.delta_y < 0)
		offset.y = -20;
	else
		offset.y = 20;
	t_ivec	map_pos;
	t_ivec	map_pos_add;
	t_ivec	map_pos_sub;

	map_pos.x = game->player.position.x / 64.0;
	map_pos.y = game->player.position.y / 64.0;
	map_pos_add.x =(game->player.position.x + offset.x) / 64.0;
	map_pos_add.y = (game->player.position.y + offset.y) / 64.0;
	map_pos_sub.x = (game->player.position.x - offset.x) / 64.0;
	map_pos_sub.y = (game->player.position.y - offset.y) / 64.0;
	if (keycode == 'w')
	{
		if (game->map[map_pos.y][map_pos_add.x] == 0)
			game->player.position.x += game->player.delta_x;
		if (game->map[map_pos_add.y][map_pos.x] == 0)
			game->player.position.y += game->player.delta_y;
	}
	if (keycode == 's')
	{
		if (game->map[map_pos.y][map_pos_sub.x] == 0)
			game->player.position.x -= game->player.delta_x;
		if (game->map[map_pos_sub.y][map_pos.y] == 0)
			game->player.position.y -= game->player.delta_y;
	}
	if (keycode == 'd')
	{
		game->player.angle += 0.1f;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		game->player.delta_x = cos(game->player.angle) * 5;
		game->player.delta_y = sin(game->player.angle) * 5;
	}
	if (keycode == 'a')
	{
		game->player.angle -= 0.1f;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.delta_x = cos(game->player.angle) * 5;
		game->player.delta_y = sin(game->player.angle) * 5;
	}
}