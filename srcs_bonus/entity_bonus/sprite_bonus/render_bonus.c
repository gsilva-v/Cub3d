#include <cub3d_bonus.h>

int	sprite_render(t_game *game)
{
	sprite_update(game);
	draw_sprite(game, game->sprite_pos, &game->resources.enemy);
}