/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:37:14 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/24 05:48:42 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static bool	init_philos(t_world *world);

bool	alloc_world_entities(t_world *world)
{
	world->forks = ft_calloc(world->philo_number, sizeof(*world->forks));
	world->philos = ft_calloc(world->philo_number, sizeof(*world->philos));
	world->threads = ft_calloc(world->philo_number, sizeof(*world->threads));
	if (pthread_mutex_init(world->dead_philo.mutex, 0) == 0)
		world->dead_philo.taken = 1;
	if (!world->forks || !world->philos || !world->threads || \
			!world->dead_philo.taken)
	{
		if (!world->forks)
			printf("Error: failed to allocate forks\n");
		if (!world->philos)
			printf("Error: failed to allocate philos\n");
		if (!world->threads)
			printf("Error: failed to allocate threads\n");
		if (!world->dead_philo.taken)
			printf("Error: failed to init dead_philo mutex\n");
		free_world_entities(world);
		return (false);
	}
	return (init_philos(world));
}

void	free_world_entities(t_world *world)
{
	u_long	i;

	if (world->forks)
	{
		i = 0;
		while (i < world->philo_number)
		{
			pthread_mutex_destroy(world->forks[i].mutex);
			i += 1;
		}
		free(world->forks);
	}
	if (world->dead_philo.taken)
		pthread_mutex_destroy(world->dead_philo.mutex);
	if (world->philos)
		free(world->philos);
	if (world->threads)
		free(world->threads);
}

static bool	init_philos(t_world *world)
{
	u_long	i;

	i = 0;
	while (i < world->philo_number)
	{
		if (pthread_mutex_init(world->forks[i].mutex, NULL) != 0)
		{
			printf("Error: failed to init mutex %lu\n", i);
			free_world_entities(world);
			return (false);
		}
		world->philos[i].id = i + 1;
		world->philos[i].meals_left = world->meals_number;
		if (i % 2)
		{
			world->philos[i].left = &world->forks[(i + 1) % world->philo_number];
			world->philos[i].right = &world->forks[i];
		}
		else
		{
			world->philos[i].left = &world->forks[i];
			world->philos[i].right = &world->forks[(i + 1) % world->philo_number];
		}
		world->philos[i].world = world;
		i += 1;
	}
	return (true);
}
