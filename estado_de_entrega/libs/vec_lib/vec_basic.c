/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:42:15 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 17:42:20 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

float	vec_dist(t_vec v1, t_vec v2)
{
	return (sqrt((v1.x - v2.x) * (v1.x - v2.x) + \
	(v1.y - v2.y) * (v1.y - v2.y)));
}
