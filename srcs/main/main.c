#include <cub3d.h>

int main(int argc, char **argv)
{
	t_game game;

	ft_bzero(&game, sizeof(game));
	if (parse_resources(&game, argv[1]))
		return (1);
	if (parse_map(&game, argv[1]))
		return (1);
	for (int y = 0; game.map[y]; y++)
		printf("%s\n", game.map[y]);
	init_game(&game);
	for (int y = 0; game.map[y]; y++)
		printf("%s\n", game.map[y]);
	load_imgs(&game);
	game_run(&game);

	return(0);

}