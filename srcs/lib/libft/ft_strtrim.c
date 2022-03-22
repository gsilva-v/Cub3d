/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:51:48 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/10 16:37:02 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	len;

	start = 0;
	while (s1[start] && ft_char_in_set (s1[start], set))
		start ++;
	len = ft_strlen(s1);
	while (len > start && ft_char_in_set (s1[len - 1 ], set))
		len--;
	str = (char *) malloc (sizeof(*s1) * (len - start + 1));
	i = 0 ;
	while (start < len)
		str[i ++] = s1[start ++];
	str[i] = 0 ;
	return (str);
}
