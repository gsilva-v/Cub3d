#include <cub3d.h>

int	update_map(int key_code, t_game *game)
{
	set_colisions(game);
	if (key_code == 'w')
		move_forward(game);
	if (key_code == 's')
		move_back(game);
	if (key_code == 'a')
		look_left(game);
	if (key_code == 'd')
		look_right(game);
	if (key_code == ESC)
		kill_window(game);
}

int	render_map(t_game *game)
{
	t_vec player_aux;
	t_vec player_delta_aux;

	clean_map(game);
	draw_map(game);
	draw_square(&game->canvas, game->player, 10, 0xFF);
	player_aux.x = game->player.x;
	player_aux.y = game->player.y;
	player_delta_aux.x =  game->player.x + (game->delta_player.x * 7);
	player_delta_aux.y =  game->player.y + (game->delta_player.y * 7);
	draw_rays(game);
	draw_line(player_aux, player_delta_aux, 0xFF00000, game);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
	char buffer[1024];
	sprintf(buffer, "angulo = %f\n", game->player_angle);
	mlx_string_put(game->mlx, game->win, 1, 150, 0xFF0000, buffer);
}