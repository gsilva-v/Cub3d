/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:06:31 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/10 16:36:43 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	find;

	find = ft_strlen(s);
	while (find >= 0)
	{
		if (s[find] == (unsigned char)c)
			return ((char *) s + find);
		find --;
	}
	return (0);
}
