/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:50:00 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/25 17:34:51 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"
# include "sys/time.h"

typedef struct s_philo_utils
{
	pthread_mutex_t	*forks;
	int				size;
	int				philo_num;
	char			**av;
	size_t			start_time;
	int				finished;
	int				stop;
	pthread_mutex_t	print;
}	t_philo_utils;

typedef struct s_philo
{
	t_philo_utils	*utils;
	pthread_t		philo_thread;
	int				philo_id;
	size_t			last_eat;
	int				eat_counter;
	int				finished;
	int				right_fork;
}	t_philo;

size_t		ft_strlen(const char *s);
long long	ft_atoi(char *nb);
void		ft_error(char *msg);
size_t		ft_time_now(void);
void		ft_sleep(int time, t_philo_utils *utils);
int			current_programe_time(t_philo_utils *utils);
void		death_check(t_philo_utils *utils, t_philo *philo);
int			check_eat_done(t_philo *philo, t_philo_utils utils);
void		ft_print(t_philo *philo, char *msg);

#endif