/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/19 20:07:56 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_philo_struct(char **av, t_philo *utils)
{
	int i;

	i = 0;
	utils->size = ft_atoi(av[0]);
	while (i < utils.size)
	{
		utils->philos[i] = (pthread_t)malloc(sizeof(pthread_t));
		utils->forks[i] = (pthread_mutex_t)malloc(sizeof(pthread_mutex_t));
		i++;
	}
	utils->philo_num = 0;
	utils->av = av;
	utils.time = 0;
}

void *routine(t_philo utils)
{
	int i;
	int right_fork;

	i = 0;
	right_fork = utils.philo_num - 1;
	if (right_fork < 0)
		right_fork = utils.size - 1;
	// philo eat here
	pthread_mutex_lock(utils.forks[utils.philo_num]);
	pthread_mutex_lock(utils.forks[right_fork]);
	printf("%d %d has taken a fork\n", utils.time, );
	while (i < ft_atoi(utils.av[3]))
	{
		usleep(1000);
		i++;
	}
	pthread_mutex_unlock(utils.forks[utils.philo_num]);
	pthread_mutex_unlock(utils.forks[right_fork]);
	i = 0;
	while (i < ft_atoi(utils.av[4]))
	{
		usleep(1000);
		i++;
	}
}

void philos_check(t_philo utils)
{
	int i;

	i = 0;
	while (i < utils.size)
	{
		utils.philo_num = i;
		pthread_create(&utils.philos[i], 0, routine, &utils);
	}
}

int main(int ac, char **av)
{
	t_philo utils;

	init_philo_struct(av, &utils);
	return (0);
}
