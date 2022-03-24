#include <cub3d.h>

static char	**check_range_rgb(char **rgb)
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

static int	comma_in_view(char *s, int index)
{
	int	tmp;

	tmp = index;
	while (index)
	{
		index--;
		if (s[index] != ' ' && s[index] != ',')
			break ;
		else if (s[index] == ',')
			return (1);
	}
	if (index == 0)
		return (1);
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

static char	**get_rgb(char **config)
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
		if (comma > 2 || (!ft_isdigit(config[1][index]) && \
		config[1][index] != ','))
			return (NULL);
		index++;
	}
	return (check_range_rgb(ft_split(config[1], ',')));
}

int	set_color_background(t_game *game, char **cfg)
{
	char	**rgb;
	int		c;

	if (!cfg[1])
		return (1);
	rgb = get_rgb(cfg);
	if (!rgb)
	{
		free_matrix(rgb);
		free_matrix(cfg);
		return (1);
	}
	c = create_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free_matrix(rgb);
	if (!ft_strncmp(cfg[0], "C", -1) && game->resources.ceil_color != -1
		|| !ft_strncmp(cfg[0], "F", -1) && game->resources.floor_color != -1)
	{
		free_matrix(cfg);
		return (1);
	}
	if (!ft_strncmp(cfg[0], "C", -1))
		game->resources.ceil_color = c;
	if (!ft_strncmp(cfg[0], "F", -1))
		game->resources.floor_color = c;
	return (0);
}
