/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:03:54 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/24 00:29:22 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <string.h>

static bool	parse_philo_specs(t_world *world, char *argv[]);

int	main(int argc, char *argv[])
{
	t_world	world;

	if (argc < 5 || argc > 6)
	{
		printf("%s philo_number time_to_die time_to_eat time_to_sleep " \
				"[meals_number]\n", argv[0]);
		return (1);
	}
	memset(&world, 0, sizeof(world));
	if (parse_philo_specs(&world, argv) == false)
		return (1);
	if (alloc_world_entities(&world) == false)
		return (1);
	threading(&world);
	free_world_entities(&world);
	return (0);
}

static bool	parse_philo_specs(t_world *world, char *argv[])
{
	world->philo_number = ft_atol(argv[1]);
	world->time_to_die = ft_atol(argv[2]);
	world->time_to_eat = ft_atol(argv[3]);
	world->time_to_sleep = ft_atol(argv[4]);
	world->meals_number = -1;
	if (argv[5])
		world->meals_number = ft_atol(argv[5]);
	if ((argv[4] && world->meals_number == 0) || \
			(world->time_to_die == 0) || \
			(world->time_to_eat == 0) || \
			(world->time_to_sleep == 0))
	{
		printf("Error\n");
		return (false);
	}
	return (true);
}
