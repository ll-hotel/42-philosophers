/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:45:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/18 16:04:14 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static long	create_philos_threads(t_table *table);
static bool	create_monitoring_thread(t_table *table);

bool	setup_routines(t_table *table)
{
	long	philos_threads_created;
	long	i;
	bool	monitoring_thread_created;

	table_set_state(table, WAIT);
	philos_threads_created = create_philos_threads(table);
	if (philos_threads_created == table->philo_nb)
		monitoring_thread_created = create_monitoring_thread(table);
	i = philos_threads_created;
	while (i > 0)
		pthread_join(table->philos[--i].thread, NULL);
	if (monitoring_thread_created)
		pthread_join(table->monitoring_thread, NULL);
	return (philos_threads_created == table->philo_nb \
			&& monitoring_thread_created);
}

static long	create_philos_threads(t_table *table)
{
	void	*routine;
	long	i;
	bool	nice;

	routine = philo_routine;
	if (table->philo_nb == 1)
		routine = philo_alone_routine;
	i = 0;
	nice = true;
	while (nice && i < table->philo_nb)
	{
		nice = (pthread_create(&table->philos[i].thread, NULL, \
					routine, &table->philos[i]) != -1);
		if (!nice)
			table_set_state(table, END);
		i++;
	}
	return (i);
}

static bool	create_monitoring_thread(t_table *table)
{
	bool	nice;

	nice = (pthread_create(&table->monitoring_thread, NULL, \
				(void *)monitoring_routine, table) != -1);
	if (!nice)
		table_set_state(table, END);
	else
	{
		table->start_time = get_ms_time();
		table_set_state(table, START);
	}
	return (nice);
}
