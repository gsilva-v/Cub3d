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

void	check_data_leaks(t_game *game)
{
	if (&game->resources.wall)
		free_block(&game->resources.wall, game);
	if (&game->resources.door)
		free_block(&game->resources.door, game);
	if (&game->resources.open_door)
		free_block(&game->resources.open_door, game);
	if (&game->resources.pov)
		free_data(game, &game->resources.pov);
	if (&game->resources.canvas)
		free_data(game, &game->resources.canvas);
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
	exit(exit_code);
}
