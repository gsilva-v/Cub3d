#include <cub3d_bonus.h>

void	show_error(t_game *game, int exit_code, char *s)
{
	printf("Error\n%s\n", s);
	finish_him(game, exit_code);
}

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

void free_animation(t_animation *animation, t_game *game)
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
	if (&who->animation)
		free_animation(&who->animation, game);
}

void	check_data_leaks(t_game *game)
{
	if (&game->resources.canvas)
		free_data(game, &game->resources.canvas);
	if (&game->resources.map)
		free_data(game, &game->resources.map);
	if (&game->resources.enemy)
		free_data(game, &game->resources.enemy);
	if (&game->resources.wall)
		free_block(&game->resources.wall, game);
	if (&game->resources.door)
		free_block(&game->resources.door, game);
	if (&game->resources.open_door)
		free_block(&game->resources.open_door, game);
	
	if (&game->ghost.sprite)
		free_sprite(&game->ghost, game);
	if (&game->final.sprite)
		free_sprite(&game->final, game);
	
}

void	finish_him(t_game *game, int exit_code)
{
	if (game->map)
		free_matrix(game->map);
	check_data_leaks(game);
	if (game->mlx && game->win)
		kill_window(game);
	if (game->buffer)
		free(game->buffer);
	if (game->z_buffer)
		free(game->z_buffer);
	exit(exit_code);
}
