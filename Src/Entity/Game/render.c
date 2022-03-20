#include <ray.h>

int	game_render(t_game *game)
{
	clear_pixels(&game->server.canvas, screenWidth, screenHeight);
	//draw_map(game);
	player_render(game);
	game->keyHandler.rotate_left = FALSE;
	game->keyHandler.rotate_right = FALSE;
	mlx_put_image_to_window(game->server.mlx, game->server.win, game->server.canvas.img, 0, 0);

	char	buffer[1024];

	mlx_mouse_show(game->server.mlx, game->server.win);
//	mlx_mouse_move(game->server.mlx, game->server.win, screenWidth / 2, screenHeight / 2);
/* 	//Information abour player's angle
	sprintf(buffer, "angle = %.3f", game->player.angle);
	mlx_string_put(game->server.mlx, game->server.win, 5, 20, 0x00FF00, buffer);

	//Information about angle's tangente

	sprintf(buffer, "tangente = %.3f", tan(game->player.angle));
	mlx_string_put(game->server.mlx, game->server.win, 130, 20, 0x00FF00, buffer);

	//Information about player's y
	sprintf(buffer, "y = %.3f", game->player.position.y);
	mlx_string_put(game->server.mlx, game->server.win, game->player.position.x - 80, game->player.position.y - 20, 0xFF0000, buffer);

	//Information about player's x
	sprintf(buffer, "x = %.3f", game->player.position.x);
	mlx_string_put(game->server.mlx, game->server.win, game->player.position.x - 80, game->player.position.y + 14, 0x0000FF, buffer); */




}

