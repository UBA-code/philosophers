/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/08 19:03:59 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo_struct(char **av, t_philo_utils *utils, t_philo *philo)
{
	int	i;

	utils->size = ft_atoi(av[0]);
	utils->forks = malloc(sizeof(pthread_mutex_t) * utils->size);
	utils->philo_num = 0;
	utils->av = av;
	utils->start_time = ft_time_now();
	utils->finished = 0;
	utils->stop = 0;
	pthread_mutex_init(&(utils->print), 0);
	i = -1;
	while (++i < utils->size)
	{
		pthread_mutex_init(&(utils->forks[i]), 0);
		pthread_mutex_init(&(philo[i].eat_mutex), 0);
		philo[i].utils = utils;
		philo[i].philo_id = i;
		philo[i].last_eat = 0;
		philo[i].eat_counter = 0;
		philo[i].finished = 0;
		philo[i].right_fork = philo[i].philo_id - 1;
		if (philo[i].right_fork < 0)
			philo[i].right_fork = utils->size - 1;
	}
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = philo_pointer;
	while (!philo->finished)
	{
		ft_print(philo, "is thinking\n");
		pthread_mutex_lock(&(philo->utils->forks[philo->right_fork]));
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&(philo->utils->forks[philo->philo_id]));
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&(philo->eat_mutex));
		philo->last_eat = current_programe_time(philo->utils);
		if (philo->utils->av[4] && ++(philo->eat_counter))
			if (philo->eat_counter == ft_atoi(philo->utils->av[4]))
				philo->finished = 1;
		pthread_mutex_unlock(&(philo->eat_mutex));
		ft_print(philo, "is eating\n");
		ft_sleep(ft_atoi(philo->utils->av[2]));
		pthread_mutex_unlock(&(philo->utils->forks[philo->right_fork]));
		pthread_mutex_unlock(&(philo->utils->forks[philo->philo_id]));
		ft_print(philo, "is sleeping\n");
		ft_sleep(ft_atoi(philo->utils->av[3]));
	}
	return (0);
}

int	philos_check(t_philo_utils *utils, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < utils->size)
	{
		if (pthread_create(&(philo[i].philo_thread), 0, routine, &(philo[i])))
			return (ft_error("Failed To create Thread\n"));
		usleep(50);
		if (pthread_detach(philo[i].philo_thread))
			return (ft_error("Failed To detach Thread\n"));
		i++;
	}
	return (0);
}

int	args_check(int ac, char **av)
{
	int	i;
	int	x;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		while (av[i])
		{
			x = 0;
			if (get_signs_len(av[i]) > 1 || !check_sign_in_num(av[i]))
				return (0);
			while (av[i][x])
				if (++x && !((av[i][x - 1] >= '0'
						&& av[i][x - 1] <= '9') || av[i][x - 1] == '+'))
					return (0);
			if (av[i][x - 1] == '+')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

int	main(int ac, char **av)
{
	t_philo_utils	utils;
	t_philo			*philo;
	int				i;

	if (!args_check(ac, av + 1))
		return (ft_error("check arguments please!\n"));
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	init_philo_struct(av + 1, &utils, philo);
	if (philos_check(&utils, philo))
		return (EXIT_FAILURE);
	while (1)
		if (!death_check(&utils, philo))
			break ;
	i = (ac * 0) - 1;
	pthread_mutex_destroy(&(utils.print));
	while (++i < utils.size)
		pthread_mutex_destroy(&(utils.forks[i]));
	return (0);
}
