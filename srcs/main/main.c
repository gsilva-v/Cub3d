#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error: invalid arguments, try ./cub3d ./maps/simple_map.cub\n");
		exit(1);
	}
	ft_bzero(&game, sizeof(game));
	if (parse_resources(&game, argv[1]))
		return (1);
	if (parse_map(&game, argv[1]))
		return (1);
	init_game(&game);
	load_imgs(&game);
	game_run(&game);
	return (0);
}
