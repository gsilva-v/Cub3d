#include "vec.h"

void	calc_matriz(float m[4][4], t_vec old, t_vec *new)
{
	new->x = old.x * m[0][0] + old.y * m[0][1] + old.y * m[0][2];
	new->y = old.x * m[1][0] + old.y * m[1][1] + old.y * m[1][2];
	new->z = old.x * m[2][0] + old.y * m[2][1] + old.y * m[2][2];
}

void	vec_scale(t_vec *v1, float scale)
{
	v1->x *= scale;
	v1->y *= scale;
}

void	vec_magnitude(t_vec *v)
{
	v->magnitude = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}
