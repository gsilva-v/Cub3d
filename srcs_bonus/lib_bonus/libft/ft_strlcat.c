/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:06:15 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/10 16:35:05 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{	
	size_t	destlen;
	size_t	d;
	size_t	s;

	destlen = ft_strlen(dest);
	d = destlen;
	s = 0;
	if (destlen >= size)
		return (size + ft_strlen(src));
	while (size > d + 1 && src[s] != '\0')
		dest[d++] = src[s++];
	if (d == size)
		dest[d] = '\0';
	dest[d] = '\0';
	return (destlen + ft_strlen(src));
}
