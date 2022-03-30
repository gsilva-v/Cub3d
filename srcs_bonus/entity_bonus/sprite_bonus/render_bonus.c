#include <cub3d_bonus.h>

int	sprite_render(t_game *game)
{
	t_animation		*animation;
	static float	elapse;
	int				index;

	if (game->lose)
	{
		draw_sprite(game, game->sprite_pos, &game->ghost.sprite);
		return (0);
	}
	elapse += game->elapsed_time;
	animation = &game->ghost.animation;
	if (elapse >= animation->seconds)
	{
		if (animation->index < animation->n_sprites - 1)
			animation->index += 1;
		else
			animation->index = 0;
		elapse = 0;
	}
	index = animation->index;
	sprite_update(game);
	draw_sprite(game, game->sprite_pos, &animation->sprites[index]);
	return (0);
}