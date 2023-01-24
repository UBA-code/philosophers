/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:53:40 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/24 21:41:07 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	skip_sign(char *nb, int *i, int *sign)
{
	int	j;

	j = 0;
	*sign = 1;
	while (nb[*i] == '-' || nb[*i] == '+')
	{
		if (nb[*i] == '-')
			*sign = -1;
		j++;
		++*i;
	}
	if (j > 1)
		return (0);
	return (1);
}

long long	ft_atoi(char *nb)
{
	size_t		i;
	int			sign;
	long long	n;

	i = 0;
	n = 0;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == ' ')
		i++;
	if (!skip_sign(nb, (int *)&i, &sign))
		ft_error("Error\n");
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		n *= 10;
		n += (nb[i] - '0');
		i++;
	}
	return (n * sign);
}

void	ft_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

int current_programe_time(t_philo_utils *utils)
{
	size_t time;

	time = ft_time_now();
	return (time - utils->start_time);
}

size_t	ft_time_now(void)
{
	struct timeval time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(int time, t_philo_utils *utils)
{
	size_t start;

	start = ft_time_now();
	while (ft_time_now() < start + time)
		usleep(10);
}


void	death_check(t_philo_utils *utils, t_philo *philo)
{
	int		i;
	size_t	time;

	while (1)
	{
		time = ft_time_now();
		i = -1;
		while (++i < utils->size)
		{
			if (check_eat_done(philo, *utils))
			{
				utils->finished = 1;
				return ;
			}
			if (time > (philo[i].last_eat + ft_atoi(utils->av[1])))
			{
				printf("%dms %d died\n", current_programe_time(utils), i + 1);
				return ;
			}
		}
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