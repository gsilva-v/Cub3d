#include <cub3d.h>

void	close_exit(int fd, char *s)
{
	close(fd);
	printf("%s\n", s);
	exit(1);
}