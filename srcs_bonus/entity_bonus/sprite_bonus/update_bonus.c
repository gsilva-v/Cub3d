#include <cub3d_bonus.h>

int	sprite_update(t_game *game)
{
	float	dist;
	t_vec	enemy_direction = game->player.pos;

	dist = vec_dist(game->player.pos, game->sprite_pos);
	vec_sub(&enemy_direction, &game->sprite_pos);
	vec_magnitude(&enemy_direction);
	vec_normalize(&enemy_direction);

	vec_scale(&enemy_direction, 1);
	vec_scale(&enemy_direction, game->elapsed_time);

	if (dist > 0.4f)
	{
		if (ft_char_in_set(game->map[(int)game->sprite_pos.y][(int)
			(game->sprite_pos.x + enemy_direction.x * 1.6f)], "03"))
			game->sprite_pos.x += enemy_direction.x;
			
		if (ft_char_in_set(game->map[(int)(game->sprite_pos.y + enemy_direction.y * \
		1.6f)][(int)game->sprite_pos.x], "03"))
			game->sprite_pos.y += enemy_direction.y;
	}
}