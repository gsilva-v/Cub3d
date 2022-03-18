#include <ray.h>

int	take_step(float dx, float dy)
{
	if (dx < 0)
		dx *= -1;
	if (dy < 0)
		dy *= -1;
	return (dx > dy ? dx : dy);
}

void drawline(t_vec vec1, t_vec vec2, int color, t_server *server)
{
	t_vec	point;
    double	dx, dy, x, y;
    int		steps;

    dx=vec2.x-vec1.x;
    dy=vec2.y-vec1.y;
    
	x = vec1.x;
	y = vec1.y;

	steps = take_step(dx, dy);
	dx = (double) (dx / steps);
	dy = (double) (dy / steps);
	while (steps--)
	{
		point = (t_vec) {.x = x, .y = y};
		put_pixel(&server->canvas, point, color);
		x += dx;
		y += dy;
	}
}
