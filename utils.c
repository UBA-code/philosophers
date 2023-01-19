/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:53:40 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/18 18:55:19 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long long	ft_atoi(char *nb)
{
	size_t		i;
	int			sign;
	long long	n;

	i = 0;
	n = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == ' ')
		i++;
	if (!skip_sign(nb, (int *)&i, &sign))
		ft_error("Error\n");
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		n *= 10;
		n += (nb[i] - '0');
		i++;
	}
	return (n * sign);
}

void	ft_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}