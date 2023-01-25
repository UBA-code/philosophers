/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:05:32 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/25 15:49:55 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int current_programe_time(t_philo_utils *utils)
{
	size_t	time;

	time = ft_time_now();
	return (time - utils->start_time);
}

size_t	ft_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(int time, t_philo_utils *utils)
{
	size_t	start;

	start = ft_time_now();
	while (ft_time_now() < start + time)
		usleep(10);
}


void	death_check(t_philo_utils *utils, t_philo *philo)
{
	int		i;

	i = 0;
	while (1)
	{
		if (check_eat_done(philo, *utils))
		{
			utils->finished = 1;
			return ;
		}
		pthread_mutex_lock(&(philo[i].utils->print));
		if (current_programe_time(utils) > (philo[i].last_eat + ft_atoi(utils->av[1]))
			&& !(philo[i].finished))
		{
			// utils->stop = 1;
			printf("%dms %d died\n", current_programe_time(utils), philo[i].philo_id + 1);
			return ;
		}
		pthread_mutex_unlock(&(philo[i].utils->print));
		i++;
		if (i == utils->size)
			i = 0;
	}
}

int	check_eat_done(t_philo *philo, t_philo_utils utils)
{
	int	i;

	i = 0;
	while (i < utils.size)
	{
		if (!philo[i].finished)
			return (0);
		i++;
	}
	return (1);
}
