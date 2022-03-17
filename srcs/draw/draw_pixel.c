#include <cub3d.h>

void	drawpixel(t_data *data, t_vec point, int color)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length + ((int)point.x) * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
