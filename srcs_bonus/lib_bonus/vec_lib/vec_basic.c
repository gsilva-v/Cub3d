#include "vec.h"

void	vec_sum(t_vec *v1, t_vec *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
}

void	vec_sub(t_vec *v1, t_vec *v2)
{
	v1->x -= v2->x;
	v1->y -= v2->y;
}

void	vec_mult(t_vec *v1, t_vec *v2)
{
	v1->x *= v2->x;
	v1->y *= v2->y;
}

void	vec_div(t_vec *v1, t_vec *v2)
{
	v1->x /= v2->x;
	v1->y /= v2->y;
}
