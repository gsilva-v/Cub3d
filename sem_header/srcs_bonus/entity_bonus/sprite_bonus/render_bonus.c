#include <cub3d_bonus.h>

static void	draw_ghosts(t_game *game)
{
	t_animation		*animation;
	int				index;

	animation = &game->resources.g_animation;
	index = 0;
	while (index < game->n_ghost)
	{
		if (game->ghost[index].found_player)
			draw_sprite(game, game->ghost[index].pos, \
			&game->resources.g_sprite);
		else
			draw_sprite(game, game->ghost[index].pos, \
			&animation->sprites[animation->index]);
		index++;
	}
}

void	sort_sprite(t_game *game)
{
	t_entity	holder;
	float		dist;
	float		next_dist;
	int			index;
	int			index2;

	index = 0;
	while (index < game->n_ghost - 1)
	{
		index2 = index + 1;
		dist = vec_dist(game->player.pos, game->ghost[index].pos);
		while (index2 < game->n_ghost)
		{
			next_dist = vec_dist(game->player.pos, game->ghost[index2].pos);
			if (next_dist > dist)
			{
				holder = game->ghost[index];
				game->ghost[index] = game->ghost[index2];
				game->ghost[index2] = holder;
			}
			index2++;
		}
		index++;
	}
}

int	sprite_render(t_game *game)
{
	t_animation		*animation;
	static float	elapse;

	elapse += game->elapsed_time;
	animation = &game->resources.g_animation;
	if (elapse >= animation->seconds)
	{
		if (animation->index < animation->n_sprites - 1)
			animation->index += 1;
		else
			animation->index = 0;
		elapse = 0;
	}
	sort_sprite(game);
	draw_ghosts(game);
	if (!game->lose)
		sprite_update(game);
	draw_sprite(game, game->final.pos, &game->final.sprite);
	return (0);
}
