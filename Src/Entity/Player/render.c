#include <ray.h>

int	player_render(t_game *game)
{
	t_vec	final;
	t_vec	initial;

	initial = (t_vec){
		.x = game->player.position.x,
		.y = game->player.position.y
	};
	final = (t_vec){
		.x = game->player.position.x + (game->player.delta_x * 3),
		.y = game->player.position.y + (game->player.delta_y * 3),
	};
	drawsquare(game->player.position, 10, 0xFF, &game->server);
	drawline(initial, final, 0xFFFF00, &game->server);//draw line direction
	
	initial = (t_vec) {.x = game->player.position.x, .y = 0};
	final = (t_vec) {.x = game->player.position.x, .y = game->player.position.y};
	drawline(initial, final, 0xFF0000, &game->server); // player's y axis

	initial = (t_vec) {.x = 0, .y = game->player.position.y};
	final = (t_vec) {.x = game->player.position.x, .y = game->player.position.y};
	drawline(initial, final, 0x0000FF, &game->server); // player's x axis
	raycasting(game);
}
