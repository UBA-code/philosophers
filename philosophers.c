/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/22 23:41:07 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void init_philo_struct(char **av, t_philo_utils *utils, t_philo *philo)
{
	int i;
	int right_fork;

	utils->size = ft_atoi(av[0]);
	utils->philos = malloc(sizeof(pthread_t) * utils->size);
	utils->forks = malloc(sizeof(pthread_mutex_t) * utils->size);
	i = -1;
	utils->eating_times = malloc(sizeof(int) * utils->size);
	while (++i < utils->size)
		utils->eating_times[i] = 0;
	utils->philo_num = 0;
	utils->av = av;
	utils->start_time = ft_time_now();
	i = 0;
	// philo = malloc(sizeof(t_philo) * utils->size);
	while (i < utils->size)
	{
		pthread_mutex_init(&(utils->forks[i]), 0);
		philo[i].utils = utils;
		philo[i].philo_thread = malloc(sizeof(pthread_t));
		philo[i].philo_id = i;
		philo[i].last_eat = ft_time_now();
		right_fork = philo[i].philo_id - 1;
		if (right_fork < 0)
			right_fork = utils->size;
		philo[i].right_fork = &(utils->forks[right_fork]);
		philo[i].left_fork = &(utils->forks[philo->philo_id]);
		// philo[i].eat_counter = 0;
		// philo[i].finished = 0;
		// (*philo)[i].forks = utils->forks;
		i++;
	}
}

void *routine(void *philo_pointer)
{
	int		right_fork;
	t_philo	*philo;

	philo = philo_pointer;
	right_fork = philo->philo_id - 1;
	if (right_fork < 0)
		right_fork = philo->utils->size - 1;
	// philo eat here
	while (1)
	{
		printf("%dms %d is thinking\n", current_programe_time(philo->utils), philo->philo_id + 1);
		pthread_mutex_lock(&(philo->utils->forks[right_fork]));      //lock right fork
		printf("%dms %d has taken a fork\n", current_programe_time(philo->utils), philo->philo_id + 1);
		pthread_mutex_lock(&(philo->utils->forks[philo->philo_id])); //lock left fork
		printf("%dms %d has taken a fork\n", current_programe_time(philo->utils), philo->philo_id + 1);
		printf("%dms %d is eating\n", current_programe_time(philo->utils), philo->philo_id + 1);
		ft_sleep(ft_atoi(philo->utils->av[2]), philo->utils);
		philo->last_eat = ft_time_now();
		pthread_mutex_unlock(&(philo->utils->forks[philo->philo_id]));
		pthread_mutex_unlock(&(philo->utils->forks[right_fork]));
		printf("%dms %d is sleeping\n", current_programe_time(philo->utils), philo->philo_id + 1);
		ft_sleep(ft_atoi(philo->utils->av[3]), philo->utils);
		// if (philo->utils->av[4] && philo->eat_counter == ft_atoi(philo->utils->av[4]))
		// {
		// 	philo->finished = 1;
		// 	pthread_detach(philo->philo_thread);
		// 	return (0);
		// }
		// philo->eat_counter++;
	}
	return (0);
}

void philos_check(t_philo_utils *utils, t_philo *philo)
{
	int i;

	i = 0;
	// philo = malloc(sizeof(t_philo) * utils->size);
	// (*(philo))->utils = utils;
	while (i < utils->size)
	{
		// philo[i]->philo_thread = malloc(sizeof(pthread_t));
		// philo[i]->philo_id = i;
		// philo[i]->last_eat = 0;
		// philo[i]->forks = utils->forks;
		pthread_create(&(philo[i].philo_thread), 0, routine, &(philo[i]));
		usleep(50);
		i++;
	}
}

int main(int ac, char **av)
{
	t_philo_utils	utils;
	t_philo			*philo;
	int i;
	size_t time;

	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	init_philo_struct(av + 1, &utils, philo);
	philos_check(&utils, philo);
	// while (1)
	// {
	// 	printf("--------  %d -------\n", philo[0].last_eat);
	// 	ft_sleep(2000, &utils);
	// }
	// check death
	while (1)
	{
		time = ft_time_now();
		i = 0;
		while (i < utils.size)
		{
			if (time > (philo[i].last_eat + ft_atoi(utils.av[1])))
			{
				printf("%dms %d died\n", current_programe_time(&utils), i + 1);
				printf("last eat = %zu\n", philo[i].last_eat);
				printf("death time = %lld\n", philo[i].last_eat + ft_atoi(utils.av[1]));
				printf("time now is = %zu\n", time);
				return (0);
			}
			i++;
			// printf("%llu\n", (philo[i].last_eat - utils.start_time) + ft_atoi(utils.av[1]));
		}
	}
	// system("leaks philosophers");
	return (0);
}
