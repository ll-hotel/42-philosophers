/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:52:13 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/24 05:52:44 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	threading(t_world *world)
{
	u_long	i;

	world->dead_philo.taken = -1;
	i = 0;
	while (i < world->philo_number)
	{
		if (pthread_create(&world->threads[i], NULL, \
					(void *)philo_life, &world->philos[i]) != 0)
		{
			printf("Error: failed to create thread %lu\n", i);
			// Kill threads
			return ;
		}
		i += 1;
	}
	leave_fork(&world->dead_philo, 0);
	i = 0;
	while (i < world->philo_number)
		pthread_join(world->threads[i++], NULL);
}
