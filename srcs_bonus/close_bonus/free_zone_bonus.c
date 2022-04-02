#include <cub3d_bonus.h>

void	free_data(t_game *game, t_data *data)
{
	if (data->name)
		free(data->name);
	if (data->img)
		mlx_destroy_image(game->mlx, data->img);
}

void	free_block(t_block *block, t_game *game)
{
	if (&block->ea)
		free_data(game, &block->ea);
	if (&block->we)
		free_data(game, &block->we);
	if (&block->so)
		free_data(game, &block->so);
	if (&block->no)
		free_data(game, &block->no);
}

void	free_animation(t_animation *animation, t_game *game)
{
	while (animation->n_sprites)
	{
		free_data(game, &animation->sprites[animation->n_sprites - 1]);
		animation->n_sprites--;
	}
	if (animation->sprites)
		free(animation->sprites);
}

void	free_sprite(t_entity *who, t_game *game)
{
	if (&who->sprite)
		free_data(game, &who->sprite);
}
