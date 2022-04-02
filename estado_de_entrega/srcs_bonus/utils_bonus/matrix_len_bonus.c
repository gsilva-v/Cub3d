/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_len_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:29:19 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/04/02 13:29:20 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	matrix_len(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (-1);
	while (matrix[i])
		i++;
	return (i);
}
