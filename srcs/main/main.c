#include <cub3d.h>

int main(int argc, char **argv)
{
	t_game game;

	ft_bzero(&game, sizeof(game));
	if (parse_resources(&game, argv[1]))
		return (1);
	if (parse_map(&game, argv[1]))
		return (1);
	init_game(&game);
	load_imgs(&game);
	game_run(&game);

	return(0);

}