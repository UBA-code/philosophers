/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/18 16:49:04 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *my_turn()
{
	while (1)
	{
		sleep(1);
		printf("NOK NOK\n");
	}
	return (0);
}

void ur_turn()
{
	while (1)
	{
		sleep(3);
		printf("who is there\n");
	}
}

int main ()
{
	pthread_t thread;
	pthread_create(&thread, NULL, my_turn, NULL);

	ur_turn();
	return  (0);
}