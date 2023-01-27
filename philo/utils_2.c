/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:01:56 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/27 14:02:05 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	stop_threads(t_philo_utils *utils, t_philo *philo)
{
	int	i;

	i = -1;
	utils->stop = 1;
	while (++i < utils->size)
		pthread_join(philo[i].philo_thread, 0);
}
