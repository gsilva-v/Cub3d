#include <cub3d.h>

char map[8][8] = {
	{1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,1},
	{1,0,0,0,1,0,0,1},
	{1,1,1,1,1,1,1,1}
};


int main(void)
{
	t_game datas;

	datas.player = (t_vec){.x = 64, .y = 64};
	datas.player_angle = 0;
	datas.delta_player.x = cos(datas.player_angle) * 5;
	datas.delta_player.y = sin(datas.player_angle) * 5;
	datas.mlx = mlx_init();
	datas.win = mlx_new_window(datas.mlx, 64 * 16, 64 * 8, "RAY");
	datas.canvas.img = mlx_new_image(datas.mlx, 64 * 16, 64 * 8);
	datas.canvas.addr = mlx_get_data_addr(datas.canvas.img, &datas.canvas.bits_per_pixel, &datas.canvas.line_length, &datas.canvas.endian);
	mlx_loop_hook(datas.mlx, render_map, &datas);
	mlx_hook(datas.win, KeyPress, KeyPressMask, update_map, &datas);
	mlx_loop(datas.mlx);

	return(0);

}