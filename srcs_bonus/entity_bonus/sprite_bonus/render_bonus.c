#include <cub3d_bonus.h>

int	sprite_render(t_game *game)
{
	t_animation		*animation;
	static float	elapse;
	int				index;

		
	
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
	if (!game->lose)
		sprite_update(game);
	if (game->lose == -1)
		draw_sprite(game, game->ghost.pos, &game->ghost.sprite);
	else
		draw_sprite(game, game->ghost.pos, &animation->sprites[index]);
	draw_sprite(game, game->final.pos, &game->final.sprite);
	return (0);
}