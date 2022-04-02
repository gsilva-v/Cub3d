#include <cub3d_bonus.h>

int	take_step(float dx, float dy)
{
	if (dx < 0)
		dx *= -1;
	if (dy < 0)
		dy *= -1;
	if (dx > dy)
		return (dx);
	return (dy);
}

void	draw_line(t_vec vec1, t_vec vec2, int color, t_game *game)
{
	t_vec	d;
	t_vec	point;
	int		steps;

	d.x = vec2.x - vec1.x;
	d.y = vec2.y - vec1.y;
	point.x = vec1.x;
	point.y = vec1.y;
	steps = take_step(d.x, d.y);
	d.x = (double)(d.x / steps);
	d.y = (double)(d.y / steps);
	while (steps--)
	{
		color = get_color_shade(color, 0.999f);
		if (point.x >= 0 && point.y >= 0)
			draw_pixel(&game->resources.canvas, point, color);
		point.x += d.x;
		point.y += d.y;
	}
}
