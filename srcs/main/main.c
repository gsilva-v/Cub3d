#include <cub3d.h>

int	press_key(int key_code, t_game *game)
{
	if (key_code == 'w')
		game->buttons.up = 1;
	if (key_code == 'a')
		game->buttons.left = 1;
	if (key_code == 's')
		game->buttons.down = 1;
	if (key_code == 'd')
		game->buttons.right = 1;
	if (key_code == ' ')
		game->buttons.function = 1;
	if (key_code == ESC)
		game->buttons.exit = 1;
	if (key_code == 65363)//seta direita
		game->buttons.rotate_right = 1;
	if (key_code == 65361)//seta esquerda
		game->buttons.rotate_left = 1;
}

int	release_key(int key_code, t_game *game)
{
	if (key_code == 'w')
		game->buttons.up = 0;
	if (key_code == 'a')
		game->buttons.left = 0;
	if (key_code == 's')
		game->buttons.down = 0;
	if (key_code == 'd')
		game->buttons.right = 0;
	if (key_code == ' ')
		game->buttons.function = 0;
	if (key_code == ESC)
		game->buttons.exit = 0;
	if (key_code == 65363)//seta direita
		game->buttons.rotate_right = 0;
	if (key_code == 65361)//seta esquerda
		game->buttons.rotate_left = 0;
}


int main(void)
{
	t_game game;

	game = (t_game){
		.map = {
		{1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,2,0,0,1},
		{1,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,1},
		{1,0,0,0,1,0,0,1},
		{1,1,1,1,1,1,1,1}
	}, 
		.player = {
		.x = 2,
		.y = 2
		},
		.direction = {
			.x = 1,
			.y = 0
		},
		.plane = {
			.x = 0,
			.y = 0.66
		},
		.buttons = {0}
	};
	init_game(&game);
	load_imgs(&game);
	mlx_loop_hook(game.mlx, render_map, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, press_key, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, release_key, &game);
	mlx_loop(game.mlx);

	return(0);

}