/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:27:11 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:27:12 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	draw_pixel(t_data *data, t_vec point, int color)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_len \
	+ ((int)point.x) * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_data *data, t_vec point)
{
	char	*dst;

	dst = data->addr + (((int)point.y) * data->line_len \
	+ ((int)point.x) * (data->bpp / 8));
	return (*(unsigned int *)dst);
}
