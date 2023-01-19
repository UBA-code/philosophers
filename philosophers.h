/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:50:00 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/19 20:06:11 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"

typedef struct s_philo
{
	pthread_t		*philos;
	pthread_mutex_t *forks;
	int				size;
	int				philo_num;
	char			**av;
	int				time;
}	t_philo;

size_t	ft_strlen(const char *s);
long long	ft_atoi(char *nb);
void	ft_error(char *msg);

#endif