/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/20 20:05:36 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void init_philo_struct(char **av, t_philo_utils *utils)
{
	int i;

	utils->size = ft_atoi(av[0]);
	utils->philos = malloc(sizeof(pthread_t) * utils->size);
	utils->forks = malloc(sizeof(pthread_mutex_t) * utils->size);
	i = -1;
	utils->eating_times = malloc(sizeof(int) * utils->size);
	while (++i < utils->size)
		utils->eating_times[i] = 0;
	utils->philo_num = 0;
	utils->av = av;
	gettimeofday(&utils->current_time, 0);
	gettimeofday(&utils->start_time, 0);
}

void *routine(void *philo_pointer)
{
	int right_fork;
	t_philo philo;

	philo = philo_pointer;
	right_fork = philo_num - 1;
	if (right_fork < 0)
		right_fork = utils->size - 1;
	// philo eat here
	while (1)
	{
		printf("%dms %d is thinking\n", get_current_time(*utils), philo_num + 1);
		pthread_mutex_lock(&(utils->forks[philo_num])); //lock left fork
		printf("%dms %d has taken a fork\n", get_current_time(*utils), philo_num + 1);
		pthread_mutex_lock(&(utils->forks[right_fork]));      //lock right fork
		printf("%dms %d has taken a fork\n", get_current_time(*utils), philo_num + 1);
		utils->eating_times[philo_num] = get_current_time(*utils);
		printf("%dms %d is eating\n", get_current_time(*utils), philo_num + 1);
		ft_sleep(ft_atoi(utils->av[2]));
		utils->eating_times[philo_num] = get_current_time(*utils);
		pthread_mutex_unlock(&(utils->forks[philo_num]));
		pthread_mutex_unlock(&(utils->forks[right_fork]));
		printf("%dms %d is sleeping\n", get_current_time(*utils), philo_num + 1);
		ft_sleep(ft_atoi(utils->av[3]));
	}
	return (0);
}

void philos_check(t_philo_utils *utils, t_philo philo)
{
	int i;

	i = 0;
	philo = malloc(sizeof(t_philo));
	while (i < utils->size)
	{
		philo->philo_id = i;
		philo->last_eat = 0;
		philo->forks = utils->forks;
		pthread_create(&utils->philos[i], 0, routine, &philo);
		i++;
	}
}

int main(int ac, char **av)
{
	t_philo_utils	utils;
	t_philo			*philo;
	int i;
	int time;

	init_philo_struct(av + 1, &utils);
	philos_check(&utils, &philo);
	// check death
	while (1)
	{
		gettimeofday(&utils.current_time, 0);
		time = get_current_time(utils);
		i = 0;
		while (i < utils.size)
		{
			if (time > (utils.eating_times[i] + ft_atoi(utils.av[1])))
			{
				printf("%dms %d died\n", time, i + 1);
				return (0);
			}
			i++;
		}
	}
	return (0);
}
