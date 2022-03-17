#include <cub3d.h>


void	draw_square(t_data *canvas, t_vec point, int size, int color)
{
	int	x;
	int	y;


	x = point.x;
	while (x < point.x + size)
	{
		y = point.y;
		while (y < point.y + size)
		{
			drawpixel(canvas, (t_vec){ .x = x, .y = y}, color);
			y++;
		}
		x++;
	}
	
}