/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:26:19 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:26:20 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static void	shift_color(int *a, int *b, int *c)
{
	int	d;

	d = *a - 255;
	*b += d / 2;
	*c += d / 2;
	*a = 255;
}

static int	get_color_shade(int color, double qnt_shade)
{
	int	r;
	int	g;
	int	b;

	r = ((color & (0xFF << 16)) >> 16) * qnt_shade;
	g = ((color & (0xFF << 8)) >> 8) * qnt_shade;
	b = (color & 0xFF) * qnt_shade;
	if (r > 255)
		shift_color(&r, &g, &b);
	if (g > 255)
		shift_color(&g, &r, &b);
	if (b > 255)
		shift_color(&b, &g, &r);
	if (r > 255)
		r = 255;
	if (b > 255)
		b = 255;
	if (g > 255)
		g = 255;
	return (create_rgb(r, g, b));
}

int	lamp(int x, int y, t_game *game, int color)
{
	float	dist;
	t_vec	mid_screen;
	t_vec	point;

	point = (t_vec){.x = x, .y = y};
	mid_screen = (t_vec){.x = SCREENWIDTH / 2, .y = SCREENHEIGHT / 2};
	dist = distance(point, mid_screen);
	if (dist < 400 && game->buttons.light)
		color = get_color_shade(color, 1 + (((2.f * dist) / 400 - 2.f) * -1));
	return (color);
}

int	reshade(int main_color, int have_reshade)
{
	int	color;

	color = get_color_shade(main_color, 0.6);
	if (have_reshade == 1)
		color = get_color_shade(main_color, 0.6);
	return (color);
}
