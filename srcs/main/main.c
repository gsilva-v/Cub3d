#include <cub3d.h>

int main(void)
{
	t_game game;

	game = (t_game){
		.map = {
		{1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,1},
		{1,0,0,0,2,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0,1},
		{1,0,0,0,1,0,0,1},
		{1,1,1,1,1,1,1,1}
	}};
	init_game(&game);
	load_imgs(&game);
	mlx_loop_hook(game.mlx, render_map, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, update_map, &game);
	mlx_loop(game.mlx);

	return(0);

}