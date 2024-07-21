/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:25:05 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 15:21:28 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

static bool	table_set_specs(t_table *table, const char **argv);
static void	table_init_philos(t_table *table);

bool	create_table(t_table *table, const char **argv)
{
	memset(table, 0, sizeof(*table));
	if (!table_set_specs(table, argv))
		return (false);
	pthread_mutex_init(&table->state_mutex, NULL);
	table->philos = ft_calloc(table->philo_nb, sizeof(*table->philos));
	if (!table->philos)
		return (false);
	table_init_philos(table);
	return (true);
}

void	free_table(t_table *table)
{
	long	i;

	if (table->philos)
	{
		i = 0;
		while (i < table->philo_nb)
			pthread_mutex_destroy(&table->philos[i++].own_fork.mutex);
		free(table->philos);
	}
	pthread_mutex_destroy(&table->state_mutex);
}

long	table_get_state(t_table *table)
{
	long	tmp;

	pthread_mutex_lock(&table->state_mutex);
	tmp = table->state;
	pthread_mutex_unlock(&table->state_mutex);
	return (tmp);
}

static bool	table_set_specs(t_table *table, const char **argv)
{
	table->philo_nb = ft_atol(argv[1]);
	if (table->philo_nb <= 0)
		return (puterr("Bad philo_nb\n"), false);
	table->time_to_die = ft_atol(argv[2]);
	if (table->time_to_die <= 0)
		return (puterr("Bad time_to_die\n"), false);
	table->time_to_eat = ft_atol(argv[3]);
	if (table->time_to_eat <= 0)
		return (puterr("Bad time_to_eat\n"), false);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->time_to_sleep <= 0)
		return (puterr("Bad time_to_sleep\n"), false);
	table->meals_to_eat = -1;
	if (argv[5])
	{
		table->meals_to_eat = ft_atol(argv[5]);
		if (table->meals_to_eat <= 0)
			return (puterr("Bad meals_to_eat\n"), false);
	}
	return (true);
}

static void	table_init_philos(t_table *table)
{
	t_philo	*philo;
	long	i;

	i = 0;
	while (i < table->philo_nb)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->table = table;
		pthread_mutex_init(&philo->own_fork.mutex, NULL);
		philo->own_fork.available = true;
		philo->left_fork = &philo->own_fork;
		philo->right_fork = &table->philos[(i + 1) % table->philo_nb].own_fork;
		philo->meals_left = table->meals_to_eat;
		i++;
	}
}
