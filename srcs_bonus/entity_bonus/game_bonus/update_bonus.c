#include <cub3d_bonus.h>

void	game_update(t_game *game)
{
	float	dist;

	dist = vec_dist(game->player.pos, game->sprite_pos);
	if (dist < 0.5f && game->enemy_on_view)
		game->lose = 1;
	if (game->buttons.exit)
		finish_him(game, 0);
}
