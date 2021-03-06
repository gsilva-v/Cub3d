/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:42:23 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 17:42:27 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	v->magnitude = sqrt((v->x * v->x) + (v->y * v->y));
}

int	vec_equal(t_vec v1, t_vec v2)
{
	return (fabs(v1.x - v2.x) < 0.1 && fabs(v1.y - v2.y) < 0.1);
}
