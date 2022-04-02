/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 09:05:40 by gabriel           #+#    #+#             */
/*   Updated: 2022/03/23 13:58:20 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*new;
	int		n;
	int		s;

	s = 0;
	n = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (new == NULL)
		return (NULL);
	while (s1[n] != '\0')
	{	
		new[n] = s1[n];
		n++;
	}
	while (s2[s] != '\0')
	{
		new[n + s] = s2[s];
		s++;
	}
	new[n + s] = '\0';
	free(s1);
	return (new);
}
