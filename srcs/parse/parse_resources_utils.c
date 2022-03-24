#include <cub3d.h>

static int	set_name_text(t_game *game, char **config)
{
	t_block		*wall;

	wall = &game->resources.wall;
	if (!ft_strncmp(config[0], "NO", -1) && wall->no.name)
		return (1);
	if (!ft_strncmp(config[0], "SO", -1) && wall->so.name)
		return (1);
	if (!ft_strncmp(config[0], "WE", -1) && wall->we.name)
		return (1);
	if (!ft_strncmp(config[0], "EA", -1) && wall->ea.name)
		return (1);
	if (!ft_strncmp(config[0], "NO", -1) && config[1])
		wall->no.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "SO", -1) && config[1])
		wall->so.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "WE", -1) && config[1])
		wall->we.name = ft_strdup(config[1]);
	if (!ft_strncmp(config[0], "EA", -1) && config[1])
		wall->ea.name = ft_strdup(config[1]);
	return (0);
}

static int	check_first_index(char *config)
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

static int	my_access(char **config)
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


int	valid_conf(char **config)
{
	int	valid;

	if (config)
	{
		if (config[0][0] != '\n' && matrix_len(config) != 2)
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
