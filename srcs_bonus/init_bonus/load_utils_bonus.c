#include <cub3d_bonus.h>

int	open_xpm_file(t_data *d, t_game *game)
{
	int	trash;

	d->img = mlx_xpm_file_to_image(game->mlx, d->name, &trash, &trash);
	if (!d->img)
		return (-1);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
	return (0);
}

void	init_animation(t_game *game, t_animation *anim, char *name, int n_spr)
{
	int		index;
	char	*tmp;
	char	*tmp2;

	index = 0;
	anim->index = 0;
	anim->sprites = ft_calloc(n_spr, sizeof(t_data));
	anim->n_sprites = n_spr;
	anim->seconds = 0.2f;
	while (index < n_spr)
	{
		tmp2 = ft_itoa(index);
		tmp = ft_strjoin(ft_strdup(name), tmp2);
		free (tmp2);
		tmp = ft_strjoin(tmp, ".xpm");
		anim->sprites[index].img = mlx_xpm_file_to_image(game->mlx, tmp, \
		&anim->sprites[index].width, &anim->sprites[index].height);
		anim->sprites[index].addr = \
		mlx_get_data_addr(anim->sprites[index].img, &anim->sprites[index].bpp,
				&anim->sprites[index].line_len, &anim->sprites[index].endian);
		free(tmp);
		index++;
	}
}

int	get_higher_len(char **matrix)
{
	int	index;
	int	size;
	int	tmp;

	index = 0;
	size = 0;
	while (matrix[index])
	{
		tmp = ft_strlen(matrix[index]);
		if (tmp > size)
			size = tmp;
		index++;
	}
	return (size);
}

void	clean_minimap(t_game *game)
{
	int	col;
	int	line;

	col = 0;
	line = 0;
	while (line < matrix_len(game->map) * MBS)
	{
		col = 0;
		while (col < get_higher_len(game->map) * MBS)
		{
			draw_pixel(&game->resources.map, (t_vec){.x = col, .y = line}, \
			0x0);
			col++;
		}
		line++;
	}
}
