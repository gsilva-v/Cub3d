#include <cub3d_bonus.h>

void	draw_circle(t_vec position, int radius, t_data *data, int color)
{
	int	point_x;
	int	point_y;
	int	ang;

	ang = 0;
	while (ang < 360)
	{
		point_x = radius * cosf(ang);
		point_y = radius * sinf(ang);
		draw_pixel(data, (t_vec){.x = point_x + position.x, \
		.y = point_y + position.y}, color);
		ang++;
	}
}
