#include <cub3d_bonus.h>

void	game_update(t_game *game)
{
	float	dist_enemy;
	float	dist_win;

	dist_enemy = vec_dist(game->player.pos, game->ghost.pos);
	if (dist_enemy < 0.5f && game->ghost.is_on_view)
		game->lose = -1;
	dist_win = vec_dist(game->player.pos, game->final.pos);
	if (dist_win < 0.5f && !game->lose && game->final.is_on_view)
		game->lose = 1;
	
	if (game->buttons.exit)
		finish_him(game, 0);
}
