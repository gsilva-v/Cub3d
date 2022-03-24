#include <cub3d.h>

int	set_color_background(t_game *game, char **config)
{
	char	**rgb;
	int		c;

	if (!config[1])
		return (1);
	rgb = ft_split(config[1], ',');
	if (matrix_len(rgb) != 3)
	{
		free_matrix(rgb);
		free_matrix(config);
		return (1);
	}
	c = create_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (!ft_strncmp(config[0], "C", -1))
		game->resources.ceil_color = c;
	if (!ft_strncmp(config[0], "F", -1))
		game->resources.floor_color = c;
	free_matrix(rgb);
	return (0);
}

int	my_access(char **config)
{
	int	fd;

	fd = open(config[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	set_config(t_game *game, char **config)
{
	int		fd;
	char	**rgb;

	if (!config[1])
	{
		free_matrix(config);
		return (1);
	}
	if ((ft_strncmp(config[0], "C", 1)) && (ft_strncmp(config[0], "F", 1)))
	{
		fd = my_access(config);
		if (fd == -1)
			return (1);
	}
	set_name_text(game, config);
	if ((!ft_strncmp(config[0], "C", -1)) || (!ft_strncmp(config[0], "F", -1)))
	{
		if (set_color_background(game, config))
			return (1);
	}
	return (0);
}

int	check_config(t_resource *res)
{
	if (!res->wall.ea.name || !res->wall.we.name)
		return (1);
	if (!res->wall.no.name || !res->wall.so.name)
		return (1);
	if (res->ceil_color == -1 || res->floor_color == -1)
		return (1);
	return (0);
}

int	valid_conf(char **config)
{
	int	valid;

	if (config)
	{
		if (!check_first_index(config[0]))
			return (0);
		if (config[1] && !ft_strncmp(config[1], ".", 1))
		{
			if (!check_ext(config[1], ".xpm"))
				return (0);
		}
	}
	return (1);
}
