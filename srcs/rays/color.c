#include <cub3d.h>

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	shift_color (int *a, int *b, int *c)
{
	int	d;

	d = *a - 255;
	*b += d / 2;
	*c += d / 2;
	*a = 255;
}
int	get_color_shade(int color, double qnt_shade)
{
	int	r;
	int	g;
	int	b;

	r = ((color & (0xFF << 16)) >> 16) * qnt_shade;
	g = ((color & (0xFF << 8)) >> 8) * qnt_shade;
	b = (color & 0xFF) * qnt_shade;
	if (r > 255)
		shift_color(&r, &g, &b);
	if (g > 255)
		shift_color(&g, &r, &b);
	if (b > 255)
		shift_color(&b, &g, &r);
	if (r > 255)
		r = 255;
	if (b > 255)
		b = 255;
	if (g > 255)
		g = 255;
	return (create_rgb(r, g, b));
}
