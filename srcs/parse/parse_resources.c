#include <cub3d.h>

void	set_name_text(t_game *game, char **config)
{
	if (!ft_strncmp(config[0], "NO", -1))
		game->resources.wall.no.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "SO", -1))
		game->resources.wall.so.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "WE", -1))
		game->resources.wall.we.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "EA", -1))
		game->resources.wall.ea.name = ft_strdup(config[1]);
}

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
	{
		free_matrix(config);
		return (1);
	}
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

char	**parse_config(char *line)
{
	char	**config;
	char	*temp;

	config = ft_split(line, ' ');
	if (config && config[0] && config[1])
	{
		temp = ft_strdup(config[1]);
		free(config[1]);
		config[1] = ft_strtrim(temp, "\n");
		free(temp);
	}
	if (config)
		return (config);
	free(line);
	return (NULL);
}

char *get_resources(char *line, t_game *game, int fd)
{
	char	**config;

	config = parse_config(line);
	if (!config)
		finish_him(game, 1);
	if (line[0] != '\n' && set_config(game, config))
	{
		close(fd);
		free(line);
		finish_him(game, 1);
	}
	if (line[0] == 'C')
	{
		free(line);
		free_matrix(config);
		return (NULL);
	}
	free(line);
	free_matrix(config);
	line = get_next_line(fd);
	return (line);
}

int	parse_resources(t_game *game, char *file)
{
	int		fd;
	char	*line;
	char	**config;

	game->resources.ceil_color = -1;
	game->resources.floor_color = -1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
		line = get_resources(line, game, fd);
	close(fd);
	if (check_config(&game->resources))
		finish_him(game, 1);
	return (0);
}
