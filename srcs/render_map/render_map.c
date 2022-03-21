#include <cub3d.h>

int	update_map(int key_code, t_game *game)
{
	// set_colisions(game);
	// if (key_code == 'w')
	// 	move_forward(game);
	// if (key_code == 's')
	// 	move_back(game);
	// if (key_code == 'a')
	// 	look_left(game);
	// if (key_code == 'd')
	// 	look_right(game);
	if (key_code == ESC)
		kill_window(game);
	float rotSpeed = 0.1f;
	if(key_code == 'a')
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = game->direction.x;
      game->direction.x = game->direction.x * cos(-rotSpeed) - game->direction.y * sin(-rotSpeed);
      game->direction.y = oldDirX * sin(-rotSpeed) + game->direction.y * cos(-rotSpeed);
      double oldPlaneX = game->plane.x;
      game->plane.x = game->plane.x * cos(-rotSpeed) - game->plane.y * sin(-rotSpeed);
      game->plane.y = oldPlaneX * sin(-rotSpeed) + game->plane.y * cos(-rotSpeed);
    }
}

int	render_map(t_game *game)
{
	t_vec player_aux;
	t_vec player_delta_aux;

	clean_map(game);
	// draw_map(game);
	// draw_square(&game->canvas, game->player, 10, 0xFF);
	// player_aux.x = game->player.x;
	// player_aux.y = game->player.y;
	// // player_delta_aux.x =  game->player.x + (game->delta_player.x * 7);
	// // player_delta_aux.y =  game->player.y + (game->delta_player.y * 7);
	// draw_rays(game);
	// draw_line(player_aux, player_delta_aux, 0xFF00000, game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
	// char buffer[1024];
	// sprintf(buffer, "angulo = %f\n", game->player_angle);
	// mlx_string_put(game->mlx, game->win, 10, 10, 0xFF0000, buffer);
}