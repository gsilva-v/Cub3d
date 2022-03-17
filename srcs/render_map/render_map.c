#include <cub3d.h>

int	update_map(int key_code, t_game *datas)
{
	t_vec offset;
	t_int_vec ip;
	t_int_vec ip_add_offset;
	t_int_vec ip_sub_offset;
	
	offset.x = 20;
	if (datas->delta_player.x < 0)
		offset.x = -20;
	offset.y = 20;
	if (datas->delta_player.y < 0)
		offset.y = -20;
	ip.x = datas->player.x / 64;
	ip_add_offset.x = (datas->player.x + offset.x) / 64;
	ip_sub_offset.x = (datas->player.x - offset.x) / 64;
	ip.y = datas->player.y / 64;
	ip_add_offset.y = (datas->player.y + offset.y) / 64;
	ip_sub_offset.y = (datas->player.y - offset.y) / 64;
	
	if (key_code == 'w')
	{
		if (datas->map[ip.y][ip_add_offset.x] == 0)
			datas->player.x += datas->delta_player.x;
		if (datas->map[ip_add_offset.y][ip.x] == 0)
			datas->player.y += datas->delta_player.y;
	}
	if (key_code == 's')
	{
		if (datas->map[ip.y][ip_sub_offset.x] == 0)
			datas->player.x -= datas->delta_player.x;
		if (datas->map[ip_sub_offset.y][ip.x] == 0)
			datas->player.y -= datas->delta_player.y;
	}
	if (key_code == 'a')
	{
		datas->player_angle -= 0.1f;
		if (datas->player_angle < 0)
			datas->player_angle += 2 * PI; 
		datas->delta_player.x = cos(datas->player_angle) * 5;
		datas->delta_player.y = sin(datas->player_angle) * 5;
	}
	if (key_code == 'd')
	{
		datas->player_angle += 0.1f;
		if (datas->player_angle > 2 * PI)
			datas->player_angle -= 2 * PI; 
		datas->delta_player.x = cos(datas->player_angle) * 5;
		datas->delta_player.y = sin(datas->player_angle) * 5;
	}
	if (key_code == ESC)
	{
		mlx_clear_window(datas->mlx, datas->win);
		mlx_loop_end(datas->mlx);
		mlx_destroy_image(datas->mlx, datas->canvas.img);
		mlx_destroy_window(datas->mlx, datas->win);
		mlx_destroy_display(datas->mlx);
		free(datas->mlx);
		exit (0);
	}
}

int	render_map(t_game *datas)
{
	clean_map(datas);
	draw_map(datas);
	draw_square(&datas->canvas, datas->player, 10, 0xFF);
	drawline((t_vec){.x = datas->player.x + 5, .y = datas->player.y +5},  (t_vec){.x = datas->player.x + (datas->delta_player.x * 5), .y = datas->player.y + (datas->delta_player.y * 5)}, 0xFF00000, datas);
	draw_rays(datas);
	mlx_put_image_to_window(datas->mlx, datas->win, datas->canvas.img, 0, 0);

}