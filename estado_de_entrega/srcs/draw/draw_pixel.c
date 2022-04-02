/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:25:25 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:25:26 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_pixel(t_data *data, t_vec point, int color)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length \
	+ ((int)point.x) * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_data *data, t_vec point)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_length \
	+ ((int)point.x) * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
