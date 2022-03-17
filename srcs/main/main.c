#include <cub3d.h>

int main(void)
{
	t_game datas;

	datas = (t_game){
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
	datas.player = (t_vec){.x = BLOCK_SIZE + 20, .y = BLOCK_SIZE + 20};
	datas.player_angle = 0;
	datas.delta_player.x = cos(datas.player_angle) * 5;
	datas.delta_player.y = sin(datas.player_angle) * 5;
	datas.width = 8;
	datas.height = 8;
	datas.mlx = mlx_init();
	datas.win = mlx_new_window(datas.mlx, BLOCK_SIZE * (datas.height * 2), BLOCK_SIZE * datas.width, "RAY");
	datas.canvas.img = mlx_new_image(datas.mlx, BLOCK_SIZE * (datas.height * 2), BLOCK_SIZE * datas.width);
	datas.canvas.addr = mlx_get_data_addr(datas.canvas.img, &datas.canvas.bits_per_pixel, &datas.canvas.line_length, &datas.canvas.endian);
	int trash;
	datas.wall.img = mlx_xpm_file_to_image(datas.mlx, "./imgs/wall.xpm", &trash, &trash);
	datas.wall.addr = mlx_get_data_addr(datas.wall.img, &datas.wall.bits_per_pixel, &datas.wall.line_length, &datas.wall.endian);
	datas.door.img = mlx_xpm_file_to_image(datas.mlx, "./imgs/door.xpm", &trash, &trash);
	datas.door.addr = mlx_get_data_addr(datas.door.img, &datas.door.bits_per_pixel, &datas.door.line_length, &datas.door.endian);
	mlx_loop_hook(datas.mlx, render_map, &datas);
	mlx_hook(datas.win, KeyPress, KeyPressMask, update_map, &datas);
	mlx_loop(datas.mlx);

	return(0);

}