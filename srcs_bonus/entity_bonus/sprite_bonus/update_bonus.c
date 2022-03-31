#include <cub3d_bonus.h>

int	sprite_update(t_game *game)
{
	float	dist;
	t_vec	enemy_direction;

	enemy_direction = game->player.pos;
	dist = vec_dist(game->player.pos, game->ghost.pos);
	vec_sub(&enemy_direction, &game->ghost.pos);
	vec_magnitude(&enemy_direction);
	vec_normalize(&enemy_direction);
	vec_scale(&enemy_direction, 1.5f);
	vec_scale(&enemy_direction, game->elapsed_time);
	if (dist > 0.4f && dist < 4.f)
	{
		if (ft_char_in_set(game->map[(int)game->ghost.pos.y][(int)
				(game->ghost.pos.x + enemy_direction.x * 1.6f)], "03"))
			game->ghost.pos.x += enemy_direction.x;	
		if (ft_char_in_set(game->map[(int)(game->ghost.pos.y + \
		enemy_direction.y * 1.6f)][(int)game->ghost.pos.x], "03"))
			game->ghost.pos.y += enemy_direction.y;
	}
	return (0);
}
