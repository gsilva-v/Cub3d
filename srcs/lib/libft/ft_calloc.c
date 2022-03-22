/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:05:39 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/10 16:45:52 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbytes, size_t sizemem)
{
	void	*ptr;

	ptr = malloc(nbytes * sizemem);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, (nbytes * sizemem));
	return (ptr);
}
