#include <cub3d.h>

int	set_config(t_game *game, char **config)
{
	if ((ft_strncmp(config[0], "C", 1)) && (ft_strncmp(config[0], "F", 1)))
	{
		int fd = open(config[1], O_RDONLY);
		if (fd == -1)
			return (1);
	}
	if (!ft_strncmp(config[0], "NO", -1))
		game->resources.wall.no.name = ft_strdup(config[1]); 
	if (!ft_strncmp(config[0], "SO", -1))
		game->resources.wall.so.name = ft_strdup(config[1]); 
	if (!ft_strncmp(config[0], "WE", -1))
		game->resources.wall.we.name = ft_strdup(config[1]); 
	if (!ft_strncmp(config[0], "EA", -1))
		game->resources.wall.ea.name = ft_strdup(config[1]); 
	if ((!ft_strncmp(config[0], "C", -1)) || (!ft_strncmp(config[0], "F", -1)))
	{
		if (!config[1])
			return (1);
		char **rgb = ft_split(config[1], ',');
		if (matrix_len(rgb) != 3)
			return (1);
		if (!ft_strncmp(config[0], "C", -1))
			game->resources.ceil_color = create_rgb(ft_atoi(rgb[0]),ft_atoi(rgb[1]), ft_atoi(rgb[2])); 
		if (!ft_strncmp(config[0], "F", -1))
			game->resources.floor_color = create_rgb(ft_atoi(rgb[0]),ft_atoi(rgb[1]), ft_atoi(rgb[2])); 
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

int	parse_resources(t_game *game, char *file)
{
	int fd;
	char *line;
	char **config;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		config = ft_split(line, ' ');
		if (config && config[0] && config[1])
			config[1] = ft_strtrim(config[1], "\n");
		if(line[0] != '\n' && set_config(game, config))
		{
			free(line);
			close(fd);
			return(1);
		}
		if (line[0] == 'C')
		{
			free(line);	
			break ;
		}
		free(line);	
		line = get_next_line(fd);
	}
	close(fd);
	if (check_config(&game->resources))
		return (1);
	return (0);

}