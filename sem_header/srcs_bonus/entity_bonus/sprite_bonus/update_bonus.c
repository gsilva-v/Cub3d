#include <cub3d_bonus.h>

int	sprite_update(t_game *game)
{
	int		index;
	float	dist;
	t_vec	enemy_dir;

	index = -1;
	while (++index < game->n_ghost)
	{
		enemy_dir = game->player.pos;
		dist = vec_dist(game->player.pos, game->ghost[index].pos);
		vec_sub(&enemy_dir, &game->ghost[index].pos);
		vec_magnitude(&enemy_dir);
		vec_normalize(&enemy_dir);
		vec_scale(&enemy_dir, (float)rand() / (float)(RAND_MAX / 2));
		vec_scale(&enemy_dir, game->elapsed_time);
		if (dist > 0.4f && dist < 4.f)
		{
			if (ft_char_in_set(game->map[(int)game->ghost[index].pos.y][(int)
					(game->ghost[index].pos.x + enemy_dir.x * 1.6f)], "03"))
				game->ghost[index].pos.x += enemy_dir.x;
			if (ft_char_in_set(game->map[(int)(game->ghost[index].pos.y + \
			enemy_dir.y * 1.6f)][(int)game->ghost[index].pos.x], "03"))
				game->ghost[index].pos.y += enemy_dir.y;
		}
	}
	return (0);
}

void	ghost_on_view(t_game *game, t_vec ray_dir)
{
	int	index;

	index = 0;
	while (index < game->n_ghost)
	{
		is_on_view(game, &game->ghost[index], ray_dir);
		index++;
	}
}

void	reset_ghost_view(t_game *game)
{
	int	index;

	index = 0;
	while (index < game->n_ghost)
	{
		game->ghost[index].is_on_view = 0;
		index++;
	}
}

void	is_on_view(t_game *game, t_entity *entity, t_vec ray_dir)
{
	t_vec	dir_player_entity;

	dir_player_entity = (t_vec){
		.x = entity->pos.x - game->player.pos.x,
		.y = entity->pos.y - game->player.pos.y
	};
	vec_magnitude(&dir_player_entity);
	vec_normalize(&dir_player_entity);
	if (vec_equal(ray_dir, dir_player_entity))
		entity->is_on_view = 1;
}
