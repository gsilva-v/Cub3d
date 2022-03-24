#include <cub3d.h>

void	show_error(t_game *game, int exit_code, char *s)
{
	printf("Error: %s\n", s);
	finish_him(game, exit_code);
}
