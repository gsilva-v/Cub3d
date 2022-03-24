#include <cub3d.h>

char	**check_range_rgb(char **rgb)
{
	int	status;
	int	r;
	int	g;
	int	b;

	status = 0;
	if (matrix_len(rgb) != 3)
		status = -1;
	else
	{
		r = ft_atoi(rgb[0]);
		g = ft_atoi(rgb[1]);
		b = ft_atoi(rgb[2]);
		if (r < 0 || g < 0 || b < 0)
			status = -1;
		if (r > 255 || g > 255 || b > 255)
			status = -1;
	}
	if (status)
	{
		free_matrix(rgb);
		return (NULL);
	}
	return (rgb);
}

int	comma_in_view(char *s, int index)
{
	int	tmp;

	tmp = index;
	while (index)
	{
		index--;
		if (s[index] != ' ' && s[index] != ',')
			break;
		else if (s[index] == ',')
			return (1);
	}
	index = tmp;
	while (s[index])
	{
		if (s[index] != ' ' && s[index] != ',')
			return (0);
		else if (s[index] == ',')
			return (1);
		index++;
	}
	return (1);
}

char	**get_rgb(char **config)
{
	int	comma;
	int	index;

	comma = 0;
	index = 0;
	while (config[1][index])
	{
		if (config[1][index] == ',')
			comma++;
		if (config[1][index] == ' ' && comma_in_view(config[1], index))
		{
			index++;
			continue ;
		}
		if (comma > 2 || (!ft_isdigit(config[1][index]) && config[1][index] != ','))
			return (NULL);
		index++;
	}
	return (check_range_rgb(ft_split(config[1], ',')));
}
int	set_color_background(t_game *game, char **config)
{
	char	**rgb;
	int		c;

	if (!config[1])
		return (1);
	rgb = get_rgb(config);
	if (!rgb)
	{
		free_matrix(rgb);
		free_matrix(config);
		return (1);
	}
	c = create_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free_matrix(rgb);
	if (!ft_strncmp(config[0], "C", -1) && game->resources.ceil_color != -1 ||
		!ft_strncmp(config[0], "F", -1) && game->resources.floor_color != -1 )
	{
		free_matrix(config);
		return (1);
	}
	if (!ft_strncmp(config[0], "C", -1))
		game->resources.ceil_color = c;
	if (!ft_strncmp(config[0], "F", -1))
		game->resources.floor_color = c;
	return (0);
}

int	my_access(char **config)
{
	int	fd;

	fd = open(config[1], O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
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
		if (my_access(config))
			return (1);
	}
	if (set_name_text(game, config))
		return (1);
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
		if (config[0][0] != '\n' && matrix_len(config) != 2 )
			return (0);
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
