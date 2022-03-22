/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:02:52 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 17:48:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	*new_vec(float x, float y, float z)
{
	t_vec *vec;

	vec = (t_vec *) malloc(sizeof(t_vec));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vec	*vec_init(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

void	vec_scale(t_vec *v1, float scale)
{
	v1->x *= scale;
	v1->y *= scale;
}

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
	v1->x /=  v2->x;
	v1->y /=  v2->y;
}

void	vec_magnitude(t_vec *v)
{
	v->magnitude = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

void	vec_normalize(t_vec *v)
{
	if (v->magnitude > 0)
	{
		v->x /= v->magnitude;
		v->y /= v->magnitude;
		v->z /= v->magnitude;
	}
}

void	vec_rotate(t_vec *vec, float	angle)
{
	float	rad;
	float	x;
	float	y;
	float	z;

	x = vec->x;
	y = vec->y;
	z = vec->z;
	rad = angle * M_PI / 100;
	
	//vec->x = x * cos(rad) - y * sin(rad);
	//vec->y = y * cos(rad) + x * sin(rad);
	//vec->z = y * sin(rad) + z * cos(rad);
	vec->y = y * cos(rad) - z * sin(rad);
	vec->z = y * sin(rad) + z * cos(rad);
	vec->x = x;
}

void	vec_rotatex(t_vec *vec, float	angle)
{
	float	rad;
	float	x;
	float	y;
	float	z;

	x = vec->x;
	y = vec->y;
	z = vec->z;
	rad = angle * M_PI / 100;
	
	vec->y = y * cos(rad) - z * sin(rad);
	vec->z = y * sin(rad) + z * cos(rad);
	vec->x = x;
}

void	calc_matriz(float	m[4][4], t_vec old, t_vec *new)
{
	new->x = old.x * m[0][0] + old.y * m[0][1] + old.y *m[0][2]; 
	new->y = old.x * m[1][0] + old.y * m[1][1] + old.y *m[1][2]; 
	new->z = old.x * m[2][0] + old.y * m[2][1] + old.y *m[2][2];
}

void	vec_rotatez(t_vec *vec, float	angle)
{
	float	m[4][4] = {
		{cos(angle * M_PI / 100), sin(angle * M_PI / 100), 0, 0},
		{-sin(angle * M_PI / 100), cos(angle * M_PI / 100), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};
	t_vec	tmp;

	calc_matriz(m, *vec, &tmp);
	*vec = tmp;
}

void	vec_rotatey(t_vec *vec, float	angle)
{
	float	rad;
	float	x;
	float	y;
	float	z;

	x = vec->x;
	y = vec->y;
	z = vec->z;
	rad = angle * M_PI / 100;
	
	vec->z = z * cos(rad) - x * sin(rad);
	vec->x = z * sin(rad) + x * cos(rad);
	vec->y = y;
}

float	vec_dot_product(t_vec *vec1, t_vec *vec2)
{
	return  (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

void	change_value(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}