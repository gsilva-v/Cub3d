/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ext_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:28:49 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:28:50 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	check_ext(char *file, char *ext)
{
	int	len_map;
	int	len_ext;
	int	comp;

	comp = 0;
	len_map = ft_strlen(file);
	len_ext = ft_strlen(ext);
	while (len_ext > 0)
	{
		if (ext[--len_ext] == file[--len_map])
			comp++;
		else
			return (0);
	}
	return (1);
}
