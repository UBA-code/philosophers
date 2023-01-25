/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/25 14:02:57 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void init_philo_struct(char **av, t_philo_utils *utils, t_philo *philo)
{
	int i;

	utils->size = ft_atoi(av[0]);
	utils->forks = malloc(sizeof(pthread_mutex_t) * utils->size);
	utils->philo_num = 0;
	utils->av = av;
	utils->start_time = ft_time_now();
	utils->finished = 0;
	utils->stop = 0;
	pthread_mutex_init(&(utils->print), 0);
	// pthread_mutex_lock(&(utils->print));
	i = -1;
	while (++i < utils->size)
	{
		pthread_mutex_init(&(utils->forks[i]), 0);
		philo[i].utils = utils;
		philo[i].philo_id = i;
		philo[i].last_eat = 0;
		philo[i].eat_counter = 0;
		philo[i].finished = 0;
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
	while (!philo->finished && !philo->utils->stop)
	{
		ft_print(philo, "is thinking\n");
		// printf("%dms %d is thinking\n", current_programe_time(philo->utils), philo->philo_id + 1);
		pthread_mutex_lock(&(philo->utils->forks[right_fork]));
		ft_print(philo, "has taken a fork\n");
		// printf("%dms %d has taken a fork\n", current_programe_time(philo->utils), philo->philo_id + 1);
		pthread_mutex_lock(&(philo->utils->forks[philo->philo_id]));
		ft_print(philo, "has taken a fork\n");
		// printf("%dms %d has taken a fork\n", current_programe_time(philo->utils), philo->philo_id + 1);
		// philo->last_eat = ft_time_now();
		philo->last_eat = current_programe_time(philo->utils);
		ft_print(philo, "is eating\n");
		// printf("%dms %d is eating\n", current_programe_time(philo->utils), philo->philo_id + 1);
		ft_sleep(ft_atoi(philo->utils->av[2]), philo->utils);
		philo->eat_counter++;
		pthread_mutex_unlock(&(philo->utils->forks[philo->philo_id]));
		pthread_mutex_unlock(&(philo->utils->forks[right_fork]));
		ft_print(philo, "is sleeping\n");
		// printf("%dms %d is sleeping\n", current_programe_time(philo->utils), philo->philo_id + 1);
		ft_sleep(ft_atoi(philo->utils->av[3]), philo->utils);
		if (philo->utils->av[4] && philo->eat_counter == ft_atoi(philo->utils->av[4]))
			philo->finished = 1;
	}
	return (0);
}

void philos_check(t_philo_utils *utils, t_philo *philo)
{
	int i;

	i = 0;
	while (i < utils->size)
	{
		pthread_create(&(philo[i].philo_thread), 0, routine, &(philo[i]));
		pthread_detach(philo[i].philo_thread);
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
	death_check(&utils, philo);
	i = 0;
	while (i < utils.size)
	{
		pthread_mutex_destroy(&(utils.forks[i]));
		i++;
	}
	// system("leaks philo");
	return (0);
}
