#include <cub3d_bonus.h>

void	check_ghost_dist(t_game *game)
{
	float	dist_enemy;
	int	index;

	index = 0;
	while (index < game->n_ghost)
	{
		dist_enemy = vec_dist(game->player.pos, game->ghost[index].pos);
		if (dist_enemy < 0.5f && game->ghost[index].is_on_view)
		{
			game->lose = -1;
			game->ghost[index].found_player = 1;
			break ;
		}
		index++;
	}
}

void	game_update(t_game *game)
{
	float	dist_win;

	check_ghost_dist(game);
	dist_win = vec_dist(game->player.pos, game->final.pos);
	if (dist_win < 0.5f && !game->lose && game->final.is_on_view)
		game->lose = 1;
	if (game->buttons.exit)
		finish_him(game, 0);
}
