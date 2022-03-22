#include <cub3d.h>

int main(int argc, char **argv)
{
	t_game game;

	init_game(&game);
	load_imgs(&game);
	if (parse_resources(&game, argv[1]))
		return (1);
	if (parse_map(&game, argv[1]))
		return (1);
	game_run(&game);

	return(0);

}