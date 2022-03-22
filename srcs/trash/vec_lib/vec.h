/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:25:49 by user42            #+#    #+#             */
/*   Updated: 2022/03/21 10:44:55 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
#define VEC_H
#include <stdlib.h>
#include <math.h>

typedef struct s_vec
{
	float			x;
	float			y;
	float			z;
	float			magnitude;
	struct s_vec	*next;
} t_vec;

typedef struct s_int_vec{
	int	x;
	int	y;
}	t_int_vec;


void	vec_sum(t_vec *v1, t_vec *v2);
void	vec_sub(t_vec *v1, t_vec *v2);
void	vec_mult(t_vec *v1, t_vec *v2);
void	vec_div(t_vec *v1, t_vec *v2);
void	vec_scale(t_vec *v1, float scale);
void	vec_normalize(t_vec *v);
t_vec	*vec_init(t_vec *vec, float x, float y, float z);
t_vec	*new_vec(float x, float y, float z);
void	vec_magnitude(t_vec *v);
void	vec_rotate(t_vec *vec, float	angle);
void	vec_rotatex(t_vec *vec, float	angle);
void	vec_rotatey(t_vec *vec, float	angle);
void	vec_rotatez(t_vec *vec, float	angle);
float	vec_dot_product(t_vec *vec1, t_vec *vec2);
void	change_value(t_vec *vec, float x, float y, float z);

#endif