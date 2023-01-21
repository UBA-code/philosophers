/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:50:00 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/21 21:35:58 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/time.h"

typedef struct s_philo_utils
{
	pthread_t		*philos;
	pthread_mutex_t *forks;
	int				size;
	int				philo_num;
	char			**av;
	int				*eating_times;
	struct	timeval	current_time;
	struct	timeval	start_time;
}	t_philo_utils;

typedef struct s_philo
{
	t_philo_utils	*utils;
	pthread_t		philo_thread;
	int				philo_id;
	int				last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eat_counter;
	int				finished;
	// pthread_mutex_t	*forks;
}	t_philo;

size_t	ft_strlen(const char *s);
long long	ft_atoi(char *nb);
void	ft_error(char *msg);
void	ft_sleep(int time, t_philo_utils *utils);
int get_current_time(t_philo_utils *utils);

#endif