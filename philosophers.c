/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/18 19:11:56 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_philo_struct(char **av, t_philo utils)
{
	int i;

	i = 0;
	utils.size = ft_atoi(av[0]);
	while (i < utils.size)
	{
		utils.philos[i] = (pthread_t)malloc(sizeof(pthread_t));
		i++
	}
}

int main (int ac, char **av)
{
	t_philo utils;

	
	return  (0);
}
