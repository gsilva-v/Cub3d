#include <cub3d.h>

void	set_name_text(t_game *game, char **config)
{
	if (config && ft_strncmp(config[1], ".", 1))
		return ;
	if (!ft_strncmp(config[0], "NO", -1) && config[1])
		game->resources.wall.no.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "SO", -1) && config[1])
		game->resources.wall.so.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "WE", -1) && config[1])
		game->resources.wall.we.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "EA", -1) && config[1])
		game->resources.wall.ea.name = ft_strdup(config[1]);
}

int	check_first_index(char *config)
{
	if (!ft_strncmp(config, "NO", -1))
		return (1);
	if (!ft_strncmp(config, "SO", -1))
		return (1);
	if (!ft_strncmp(config, "WE", -1))
		return (1);
	if (!ft_strncmp(config, "EA", -1))
		return (1);
	if (!ft_strncmp(config, "C", -1))
		return (1);
	if (!ft_strncmp(config, "F", -1))
		return (1);
	if (!ft_strncmp(config, "\n", -1))
		return (1);
	return (0);
}

char	**parse_config(char *line)
{
	char	**config;
	char	*temp;
	int		valid;

	config = ft_split(line, ' ');
	if (config && config[0] && config[1])
	{
		temp = ft_strdup(config[1]);
		free(config[1]);
		config[1] = ft_strtrim(temp, "\n");
		free(temp);
	}
	valid = valid_conf(config);
	if (config && valid)
		return (config);
	free(line);
	return (NULL);
}

char	*get_resources(char *line, t_game *game, int fd)
{
	char	**config;

	config = parse_config(line);
	if (!config)
		show_error(game, 1, "this file have any misconfiguration");
	if (line[0] != '\n' && set_config(game, config))
	{
		close(fd);
		free(line);
		show_error(game, 1, "this file have any misconfiguration");
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
	if (!check_ext(file, ".cub"))
		show_error(game, 1, "invalid extension file");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		show_error(game, 1, "cannot open file map");
	line = get_next_line(fd);
	while (line)
		line = get_resources(line, game, fd);
	close(fd);
	if (check_config(&game->resources))
		show_error(game, 1, "this file have any misconfiguration");
	return (0);
}
