#include <cub3d.h>

void	draw_pixel(t_data *data, t_vec point, int color)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length + ((int)point.x) * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_pixel(t_data *data, t_vec point)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length + ((int)point.x) * (data->bits_per_pixel / 8));
	return(*(unsigned int*)dst);
}
