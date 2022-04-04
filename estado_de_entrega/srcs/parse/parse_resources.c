/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:26:14 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/04 08:49:26 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_config(t_resource *res)
{
	if (!res->wall.ea.name || !res->wall.we.name)
		return (1);
	if (!res->wall.no.name || !res->wall.so.name)
		return (1);
	if (res->ceil_color == -1 || res->floor_color == -1)
		return (1);
	return (0);
}

static void	change_char(char *s, char c, char f, int jump)
{
	int	first;
	int	index;

	index = 0;
	first = 1;
	if (!jump)
		first = 0;
	while (s[index])
	{
		if (s[index] == c && first == 0)
			s[index] = f;
		else if (s[index] == c)
			first = 0;
		index++;
	}
}

static char	**parse_config(char *line)
{
	char	**config;
	char	*temp;
	int		valid;

	if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
		change_char(line, ' ', 1, 1);
	if (line[0] == ' ')
		line[0] = 1;
	config = ft_split(line, ' ');
	if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
		change_char(config[1], 1, ' ', 0);
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
	free_matrix(config);
	return (NULL);
}

static char	*get_resources(char *line, t_game *game, int fd)
{
	char	**config;
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	if (tmp[0] == '1')
	{
		free(tmp);
		free(line);
		return (NULL);
	}
	free(tmp);
	config = parse_config(line);
	if (!config)
		show_error(game, 1, INV_CFG);
	if (line[0] != '\n' && set_config(game, config))
	{
		close(fd);
		free(line);
		free_matrix(config);
		show_error(game, 1, INV_CFG);
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
		show_error(game, 1, INV_CFG);
	return (0);
}
