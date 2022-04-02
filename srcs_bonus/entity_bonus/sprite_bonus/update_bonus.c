#include <cub3d_bonus.h>

int	sprite_update(t_game *game)
{
	int		index;
	float	dist;
	t_vec	enemy_direction;

	index = 0;
	while (index < game->n_ghost)
	{
		enemy_direction = game->player.pos;
		dist = vec_dist(game->player.pos, game->ghost[index].pos);
		vec_sub(&enemy_direction, &game->ghost[index].pos);
		vec_magnitude(&enemy_direction);
		vec_normalize(&enemy_direction);
		vec_scale(&enemy_direction, (float)rand() / (float)(RAND_MAX / 2));
		vec_scale(&enemy_direction, game->elapsed_time);
		if (dist > 0.4f && dist < 4.f)
		{
			if (ft_char_in_set(game->map[(int)game->ghost[index].pos.y][(int)
					(game->ghost[index].pos.x + enemy_direction.x * 1.6f)], "03"))
				game->ghost[index].pos.x += enemy_direction.x;
			if (ft_char_in_set(game->map[(int)(game->ghost[index].pos.y + \
			enemy_direction.y * 1.6f)][(int)game->ghost[index].pos.x], "03"))
				game->ghost[index].pos.y += enemy_direction.y;
		}
		index++;
	}
	return (0);
}
