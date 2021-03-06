/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:42:31 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 17:42:32 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	*new_vec(float x, float y, float z)
{
	t_vec	*vec;

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

void	vec_normalize(t_vec *v)
{
	if (v->magnitude > 0)
	{
		v->x /= v->magnitude;
		v->y /= v->magnitude;
		v->z /= v->magnitude;
	}
}

float	vec_dot_product(t_vec *vec1, t_vec *vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y);
}

void	change_value(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}
