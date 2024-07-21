/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:45:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 14:56:39 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static long	create_philos_threads(t_table *table);

bool	setup_routines(t_table *table)
{
	long	philos_threads_created;
	long	i;

	pthread_mutex_lock(&table->state_mutex);
	philos_threads_created = create_philos_threads(table);
	pthread_mutex_unlock(&table->state_mutex);
	i = philos_threads_created;
	while (i > 0)
		pthread_join(table->philos[--i].thread, NULL);
	return (philos_threads_created);
}

static long	create_philos_threads(t_table *table)
{
	void	*routine;
	long	i;

	routine = philo_routine;
	if (table->philo_nb == 1)
		routine = philo_alone_routine;
	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_create(&table->philos[i].thread, NULL, \
					routine, &table->philos[i]) == -1)
		{
			table->state = GRIEF;
			return (i);
		}
		i++;
	}
	return (i);
}
