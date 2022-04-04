/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:25:54 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/04 09:11:23 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	open_xpm_file(t_data *data, t_game *game)
{
	int	trash;

	data->img = mlx_xpm_file_to_image(game->mlx, data->name, \
	&trash, &trash);
	if (!data->img)
		return (-1);
	data->addr = mlx_get_data_addr(data->img, \
	&data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}

static void	load_block(t_game *game, t_block *block)
{
	if (open_xpm_file(&block->no, game))
		show_error(game, 1, "cannot open this image");
	if (open_xpm_file(&block->so, game))
		show_error(game, 1, "cannot open this image");
	if (open_xpm_file(&block->we, game))
		show_error(game, 1, "cannot open this image");
	if (open_xpm_file(&block->ea, game))
		show_error(game, 1, "cannot open this image");
}

void	load_imgs(t_game *game)
{
	t_resource	*r;

	r = &game->resources;
	r->canvas.img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	r->canvas.addr = mlx_get_data_addr(r->canvas.img, \
	&r->canvas.bits_per_pixel, &r->canvas.line_length, &r->canvas.endian);
	load_block(game, &r->wall);
}
