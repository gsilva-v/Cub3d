#include <ray.h>

void	reset_circle(float *radius)
{
	if (*radius < 0)
		*radius += 2 * PI;
	if (*radius > 2 * PI)
		*radius -= 2 * PI;
}
