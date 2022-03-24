#include <cub3d.h>

void	close_exit(int fd, char *s)
{
	close(fd);
	printf("Error\n%s\n", s);
	exit(1);
}
