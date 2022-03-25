#include <cub3d.h>


long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

double	passed_time(long time_started)
{
	return ((current_time() - time_started) / 1000.0f);
}

int	main(int argc, char **argv)
{
	t_game	game;


	// long int c = current_time();

	// printf("%ld\n", c);
	// for (unsigned long int i = 0; i < 100000000; i++)
	// 	;
	// printf("%ld\n", current_time());
	// printf("%f\n", passed_time(c));

	if (argc != 2)
	{
		printf("Error\n%s\n", WRONG_ARG);
		exit(1);
	}
	ft_bzero(&game, sizeof(game));
	game.player.pos.x = -1.0f;
	game.player.pos.y = -1.0f;
	if (parse_resources(&game, argv[1]))
		return (1);
	if (parse_map(&game, argv[1]))
		return (1);
	init_game(&game);
	load_imgs(&game);
	game_run(&game);
	return (0);
}
