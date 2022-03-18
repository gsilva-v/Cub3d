#include <ray.h>

void	put_pixel(t_data *data, t_vec point, int color)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length + ((int)point.x) * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		get_pixel(t_data *data, t_vec point)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length + ((int)point.x) * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}


void	clear_pixels(t_data *canvas, int width, int height)
{
	t_vec	point;

	point.x = 0;
	while (point.x < width)
	{
		point.y = 0;
		while (point.y < height)
		{
			put_pixel(canvas, point, 0xa9a9a9);
			point.y++;
		}
		point.x++;
	}
	
}
