#include <cub3d.h>

void fps(t_game *game)
{

	static float second;
	static int	frame;

	game->elapsed_time = passed_time(game->last_time);
	second += game->elapsed_time;
	game->last_time = current_time();
	frame++;
	if (second >= 1)
	{
		char *buffer;
		buffer =  ft_itoa(frame);
		write (1, buffer, ft_strlen(buffer));
		write(1, "\n", 1);
		frame = 0;
		second = 0;
	}
}