/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:06:00 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/10 16:29:31 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int			x;
	char		*des;
	const char	*sr;

	x = 0;
	des = (char *)dest;
	sr = (char *)src;
	if (sr == des)
		return (NULL);
	while (n--)
	{
		des[x] = sr[x];
		x++;
	}
	return (des);
}
