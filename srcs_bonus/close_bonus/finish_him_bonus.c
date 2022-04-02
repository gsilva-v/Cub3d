#include <cub3d_bonus.h>

void	show_error(t_game *game, int exit_code, char *s)
{
	printf("Error\n%s\n", s);
	finish_him(game, exit_code);
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
	if (&game->resources.floor)
		free_data(game, &game->resources.floor);
	if (game->ghost)
		free(game->ghost);
	if (&game->final.sprite)
		free_sprite(&game->final, game);
	free_animation(&game->resources.g_animation, game);
	free_data(game, &game->resources.g_sprite);
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
