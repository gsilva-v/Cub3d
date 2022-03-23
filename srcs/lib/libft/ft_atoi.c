/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:05:19 by gabriel           #+#    #+#             */
/*   Updated: 2022/03/23 18:19:39 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long int	x;
	long int	neg;
	long int	n;

	x = 0;
	neg = 1;
	n = 0;
	while ((str[x] >= 9 && str [x] <= 13) || str[x] == 32)
		x++;
	if (str[x] == '+' || str[x] == '-')
	{
		if (str[x] == '-')
			neg *= -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		n = (str[x] - '0') + (n * 10);
		x++;
	}
	return (n * neg);
}
