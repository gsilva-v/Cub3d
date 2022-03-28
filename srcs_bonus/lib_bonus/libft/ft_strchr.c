/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:06:10 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/10 16:34:00 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	find;

	find = 0;
	while (s[find] != '\0')
	{
		if (s[find] == (unsigned char)c)
			return ((char *)s + find);
		find++;
	}
	if (s[find] == (unsigned char)c)
		return ((char *)s + find);
	return (0);
}
