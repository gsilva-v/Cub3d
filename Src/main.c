#include <ray.h>

void	init_server(t_server *server)
{
	server->mlx = mlx_init();
	server->win = mlx_new_window(server->mlx, screenWidth, screenHeight, "Raycasting");
	server->canvas.img = mlx_new_image(server->mlx, screenWidth, screenHeight);
	server->canvas.addr = mlx_get_data_addr(server->canvas.img, &server->canvas.bits_per_pixel, &server->canvas.line_length, &server->canvas.endian);

}

int	main(void)
{
	static t_game	game = {
		.map = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 2, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 2, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
		},
		.player = {
			.position = {
				.x = 2,
				.y = 3
			},
			.dir = {
				.x = 0,
				.y = -1
			},
			.movement_speed = 0.2f,
			.velocity = {0},
			.strafeVelocity = {0},
			.aceleration = {.x = 0.03f, .y = 0.03f},
			.rotation_speed = 0
		},
		.plane = {
			.x = 0.66f,
			.y = 0
		},
		.keyHandler = {0},
		.last_x = 0
	};
	int	o;
	init_server(&game.server);
	game.wall.img = mlx_xpm_file_to_image(game.server.mlx, "./Resource/wall.xpm", &o, &o);
	game.wall.addr = mlx_get_data_addr(game.wall.img, &game.wall.bits_per_pixel, &game.wall.line_length, &game.wall.endian);
	game.door.img = mlx_xpm_file_to_image(game.server.mlx, "./Resource/door.xpm", &o, &o);
	game.door.addr = mlx_get_data_addr(game.door.img, &game.door.bits_per_pixel, &game.door.line_length, &game.door.endian);
	game_run(&game);
	return (0);
}