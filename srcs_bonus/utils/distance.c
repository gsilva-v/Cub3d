#include <cub3d_bonus.h>

int	distance(t_vec a, t_vec b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}
