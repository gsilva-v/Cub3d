#include <ray.h>

void drawsquare(t_vec point, int size, int color, t_server *server)
{
	int	reset_y;
	int	max_x;
	int	max_y;

	max_x = point.x + size;
	max_y = point.y + size;
	reset_y = point.y;
	while (point.x <= max_x)
	{
		while (point.y <= max_y)
		{
			put_pixel(&server->canvas, point, color);
			point.y += 1;
		}
		point.y = reset_y;
		point.x += 1;
	}
}
