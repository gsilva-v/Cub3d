#include <ray.h>

t_vec	delta_player;
float	player_angle = 0;

void	init_server(t_server *server)
{
	server->mlx = mlx_init();
	server->win = mlx_new_window(server->mlx, (WIDTH + 12 * BLOCK_SIZE) + 845, HEIGHT * BLOCK_SIZE, "Raycasting");
	server->canvas.img = mlx_new_image(server->mlx, (WIDTH * BLOCK_SIZE) + 845, HEIGHT * BLOCK_SIZE);
	server->canvas.addr = mlx_get_data_addr(server->canvas.img, &server->canvas.bits_per_pixel, &server->canvas.line_length, &server->canvas.endian);

}

int	main(void)
{
	static t_game	game = {
		.map = (char [8][12]){
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		},
		.player = {
			.position = {
				.x = 80,
				.y = 80
			},
			.angle = 0.f
		}
	};
	game.player.delta_x = cos(game.player.angle) * 5;
	int	o;
	game.player.delta_y = sin(game.player.angle) * 5;
	init_server(&game.server);
	game.wall.img = mlx_xpm_file_to_image(game.server.mlx, "./Resource/wall.xpm", &o, &o);
	game.wall.addr = mlx_get_data_addr(game.wall.img, &game.wall.bits_per_pixel, &game.wall.line_length, &game.wall.endian);
	game.door.img = mlx_xpm_file_to_image(game.server.mlx, "./Resource/door.xpm", &o, &o);
	game.door.addr = mlx_get_data_addr(game.door.img, &game.door.bits_per_pixel, &game.door.line_length, &game.door.endian);
	game_run(&game);
	return (0);
}