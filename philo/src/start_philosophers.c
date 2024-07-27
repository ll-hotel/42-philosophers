/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:45:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/27 19:39:55 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static long		create_philos_threads(t_table *table);
static u_long	get_ms_now(void);

bool	start_philosophers(t_table *table)
{
	long	philos_threads_created;
	long	i;

	pthread_mutex_lock(&table->state_mutex);
	philos_threads_created = create_philos_threads(table);
	table->start_time = get_ms_now();
	pthread_mutex_unlock(&table->state_mutex);
	i = philos_threads_created;
	while (i > 0)
		pthread_join(table->philos[--i].thread, NULL);
	return (philos_threads_created);
}

static long	create_philos_threads(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_create(&table->philos[i].thread, NULL, \
					(void *)philo_routine, &table->philos[i]) == -1)
		{
			table->state = GRIEF;
			return (i);
		}
		i++;
	}
	return (i);
}

static u_long	get_ms_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
